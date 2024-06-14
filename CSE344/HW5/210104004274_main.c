#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 1024

pthread_t manager_thread;
pthread_t* worker_threads;
int numWorkers;
int bufferSize;
volatile sig_atomic_t terminate = 0;

int regularFileCount = 0;
int fifoFileCount = 0;
int directoryCount = 0;
long totalBytesCopied = 0;

clock_t start,end;

typedef struct{
    char src[BUFFER_SIZE];
    int src_fd;
    char dest[BUFFER_SIZE];
    int dest_fd;
} Process;

typedef struct{
    Process* processes;
    int in;
    int out;
    int count;
    int capacity;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
}Buffer;

typedef struct{
    char* src;
    char* dest;
    Buffer* buffer;
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
    int done;
}ArgumentsManager;

ArgumentsManager arguments;


Buffer* createBuffer(int capacity){
    Buffer* buffer = (Buffer*) malloc(sizeof(Buffer));
    buffer->processes = (Process*) malloc(capacity * sizeof(Process));
    buffer->in = 0;
    buffer->out = 0;
    buffer->count = 0;
    buffer->capacity = capacity;

    if(pthread_mutex_init(&buffer->mutex, NULL) != 0){
        perror("Failed to initialize mutex");
        exit(EXIT_FAILURE);
    }
    if(pthread_cond_init(&buffer->not_full, NULL) != 0){
        perror("Failed to initialize not_full condition variable");
        exit(EXIT_FAILURE);
    }
    if(pthread_cond_init(&buffer->not_empty, NULL) != 0){
        perror("Failed to initialize not_empty condition variable");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void free_buffer(Buffer* buffer){
    if(buffer != NULL){
        free(buffer->processes);
        if(pthread_mutex_trylock(&buffer->mutex) == 0){
            pthread_mutex_unlock(&buffer->mutex);
        }
        if(pthread_mutex_destroy(&buffer->mutex) != 0){
            perror("Failed to destroy mutex");
            exit(EXIT_FAILURE);
        }
        if(pthread_cond_destroy(&buffer->not_full) != 0){
            perror("Failed to destroy not_full condition variable");
            exit(EXIT_FAILURE);
        }
        if(pthread_cond_destroy(&buffer->not_empty) != 0){
            perror("Failed to destroy not_empty condition variable");
            exit(EXIT_FAILURE);
        }
        free(buffer);
    }
}

void handle_signal(int sig){
    if(sig == SIGINT){
        printf("Received SIGINT, shutting down...\n");
        terminate = 1;
        if(pthread_cond_broadcast(&arguments.buffer->not_empty) != 0){
            perror("Failed to broadcast not_empty condition variable");
            exit(EXIT_FAILURE);
        }
        if(pthread_cond_broadcast(&arguments.buffer->not_full) != 0){
            perror("Failed to broadcast not_full condition variable");
            exit(EXIT_FAILURE);
        }

        // Check if the mutex is still in use
        if(pthread_mutex_trylock(&arguments.buffer->mutex) == 0){
            pthread_mutex_unlock(&arguments.buffer->mutex);
        } else {
            printf("Mutex is still locked, cannot destroy.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void copy_directory(const char* src, const char* dest, ArgumentsManager* arguments){
    DIR* src_dir = opendir(src);
    if (src_dir == NULL) {
        perror("Failed to open source directory");
        return;
    }

    struct dirent* entry; // Directory entry
    struct stat statbuf; // File status
    char src_path[BUFFER_SIZE];
    char dest_path[BUFFER_SIZE];

    while ((entry = readdir(src_dir)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

        if (stat(src_path, &statbuf) != 0) {
            printf("Failed to get status of file: %s\n", src_path);
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) { // Directory
            if(mkdir(dest_path, 0777) == -1 && errno != EEXIST){
                perror("Failed to create directory");
                continue;
            }
            directoryCount++;
            copy_directory(src_path, dest_path, arguments); // Recursive call to handle subdirectories
        } else if (S_ISREG(statbuf.st_mode)) { // Regular file
            int src_fd = open(src_path, O_RDONLY);
            if (src_fd == -1) {
                perror("Failed to open source file");
                pthread_mutex_unlock(&arguments->buffer->mutex);
                continue;
            }
            
            int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (dest_fd == -1) {
                perror("Failed to open destination file");
                close(src_fd);
                pthread_mutex_unlock(&arguments->buffer->mutex);
                continue;
            }

            if(pthread_mutex_lock(&arguments->buffer->mutex) != 0){
                perror("Failed to lock mutex");
                continue;
            }
            while (arguments->buffer->count == arguments->buffer->capacity && !terminate) {
                if(pthread_cond_wait(&arguments->buffer->not_full, &arguments->buffer->mutex) != 0){
                    perror("Failed to wait on not_full condition variable");
                    pthread_mutex_unlock(&arguments->buffer->mutex);
                    continue;
                }
            }

            if(terminate){
                if(close(src_fd) == -1){
                    perror("Failed to close source file");
                }
                if(close(dest_fd) == -1){
                    perror("Failed to close destination file");
                }
                if(pthread_mutex_unlock(&arguments->buffer->mutex) != 0){
                    perror("Failed to unlock mutex");
                }
                break;
            }

            strcpy(arguments->buffer->processes[arguments->buffer->in].src, src_path);
            arguments->buffer->processes[arguments->buffer->in].src_fd = src_fd;
            strcpy(arguments->buffer->processes[arguments->buffer->in].dest, dest_path);
            arguments->buffer->processes[arguments->buffer->in].dest_fd = dest_fd;
            arguments->buffer->in = (arguments->buffer->in + 1) % arguments->buffer->capacity;
            arguments->buffer->count++;

            if(pthread_cond_signal(&arguments->buffer->not_empty) != 0){
                perror("Failed to signal not_empty condition variable");
                pthread_mutex_unlock(&arguments->buffer->mutex);
                continue;
            }
            if(pthread_mutex_unlock(&arguments->buffer->mutex) != 0){
                perror("Failed to unlock mutex");
                continue;
            }
            regularFileCount++;
        } else if (S_ISFIFO(statbuf.st_mode)) { // FIFO file
            if(mkfifo(dest_path, 0666) == -1 && errno != EEXIST){
                perror("Failed to create FIFO file");
                continue;
            }

            if(pthread_mutex_lock(&arguments->buffer->mutex) != 0){
                perror("Failed to lock mutex");
                continue;
            }
            while (arguments->buffer->count == arguments->buffer->capacity) {
                if(pthread_cond_wait(&arguments->buffer->not_full, &arguments->buffer->mutex) != 0){
                    perror("Failed to wait on not_full condition variable");
                    pthread_mutex_unlock(&arguments->buffer->mutex);
                    continue;
                }
            }

            int src_fd = open(src_path, O_RDONLY);
            if (src_fd == -1) {
                perror("Failed to open source file");
                if(pthread_mutex_unlock(&arguments->buffer->mutex) != 0){
                    perror("Failed to unlock mutex");
                }
                continue;
            }
            
            int dest_fd = open(dest_path, O_WRONLY);
            if (dest_fd == -1) {
                perror("Failed to open destination file");
                if(close(src_fd) == -1){
                    perror("Failed to close source file");
                }
                if(pthread_mutex_unlock(&arguments->buffer->mutex) != 0){
                    perror("Failed to unlock mutex");
                }
                continue;
            }

            strcpy(arguments->buffer->processes[arguments->buffer->in].src, src_path);
            arguments->buffer->processes[arguments->buffer->in].src_fd = src_fd;
            strcpy(arguments->buffer->processes[arguments->buffer->in].dest, dest_path);
            arguments->buffer->processes[arguments->buffer->in].dest_fd = dest_fd;
            arguments->buffer->in = (arguments->buffer->in + 1) % arguments->buffer->capacity;
            arguments->buffer->count++;

            if(pthread_cond_signal(&arguments->buffer->not_empty) != 0){
                perror("Failed to signal not_empty condition variable");
                continue;
            }

            if(pthread_mutex_unlock(&arguments->buffer->mutex) != 0){
                perror("Failed to unlock mutex");
                continue;
            }
            fifoFileCount++;
        }
    }

    if(closedir(src_dir) == -1){
        perror("Failed to close source directory");
    }
}

void* manager(void* args) {
    ArgumentsManager* arguments = (ArgumentsManager*) args;
    copy_directory(arguments->src, arguments->dest, arguments); // Start copying from the source directory
    if(pthread_mutex_lock(&arguments->mutex) != 0){
        perror("Failed to lock mutex");
        exit(EXIT_FAILURE);
    }
    arguments->done = 1;
    if(pthread_cond_broadcast(&arguments->buffer->not_empty) != 0){
        perror("Failed to broadcast not_empty condition variable");
        exit(EXIT_FAILURE);
    }
    if(pthread_mutex_unlock(&arguments->mutex) != 0){
        perror("Failed to unlock mutex");
        exit(EXIT_FAILURE);
    }
    pthread_barrier_wait(&arguments->barrier);
    return NULL;
}

void* worker(void* args) {
    ArgumentsManager* arguments = (ArgumentsManager*) args;
    Buffer* buffer = arguments->buffer; 

    while (1) {
        if(pthread_mutex_lock(&buffer->mutex) != 0){
            perror("Failed to lock mutex");
            return NULL;
        }

        while (buffer->count == 0 && !arguments->done && !terminate) {
            if(pthread_cond_wait(&buffer->not_empty, &buffer->mutex) != 0){
                perror("Failed to wait on not_empty condition variable");
                return NULL;
            }
        }
        if((arguments->done && buffer->count == 0) || terminate){
            if(pthread_mutex_unlock(&buffer->mutex) != 0){
                perror("Failed to unlock mutex");
            }
            pthread_barrier_wait(&arguments->barrier);
            break;
        }

        Process process = buffer->processes[buffer->out];
        buffer->out = (buffer->out + 1) % buffer->capacity;
        buffer->count--;

        int source_fd = process.src_fd;
        int destination_fd = process.dest_fd;

        if(pthread_cond_signal(&buffer->not_full) != 0){
            perror("Failed to signal not_full condition variable");
        }

        if(pthread_mutex_unlock(&buffer->mutex) != 0){
            perror("Failed to unlock mutex");
        }

        char fileBuffer[BUFFER_SIZE];
        ssize_t bytes_read, bytes_written;

        while ((bytes_read = read(source_fd, fileBuffer, BUFFER_SIZE)) > 0) {
            bytes_written = write(destination_fd, fileBuffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("Failed to write to destination file");
                break;
            }
            pthread_mutex_lock(&arguments->mutex);
            totalBytesCopied += bytes_read;
            pthread_mutex_unlock(&arguments->mutex);
        }


        if(close(source_fd) == -1){
            perror("Failed to close source file");
        }
        if(close(destination_fd) == -1){
            perror("Failed to close destination file");
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <buffer_size> <number_of_workers> <source_directory> <destination_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    bufferSize = atoi(argv[1]);
    numWorkers = atoi(argv[2]);
    char* sourceDir = argv[3];
    char* destinationDir = argv[4];

    if (bufferSize <= 0 || numWorkers <= 0) {
        printf("Invalid buffer size or number of workers.\n");
        return EXIT_FAILURE;
    }

    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    start = clock();

    arguments.src = sourceDir;
    arguments.dest = destinationDir;
    arguments.done = 0;
    arguments.buffer = createBuffer(bufferSize);

    if(pthread_mutex_init(&arguments.mutex, NULL) != 0){
        perror("Failed to initialize mutex");
        exit(EXIT_FAILURE);
    }

    if(pthread_barrier_init(&arguments.barrier, NULL, numWorkers + 1) != 0){
        perror("Failed to initialize barrier");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&manager_thread, NULL, manager, &arguments) != 0){
        perror("Failed to create manager thread");
        exit(EXIT_FAILURE);
    }
    printf("Manager thread is created.\n");

    worker_threads = (pthread_t*)malloc(numWorkers * sizeof(pthread_t));
    for (int i = 0; i < numWorkers; i++) {
        if(pthread_create(&worker_threads[i], NULL, worker, &arguments) != 0){
            perror("Failed to create worker thread");
            exit(EXIT_FAILURE);
        }
    }
    printf("Worker threads are created.\n");

    printf("Copying files from %s to %s \n", sourceDir, destinationDir);


    if(pthread_join(manager_thread, NULL) != 0){
        perror("Failed to join manager thread");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numWorkers; i++) {
        if(pthread_join(worker_threads[i], NULL) != 0){
            perror("Failed to join worker thread");
            exit(EXIT_FAILURE);
        }
    }

    free(worker_threads);
    free_buffer(arguments.buffer);

    if(pthread_mutex_destroy(&arguments.mutex) != 0){
        perror("Failed to destroy mutex");
        exit(EXIT_FAILURE);
    }

    if(pthread_barrier_destroy(&arguments.barrier) != 0){
        perror("Failed to destroy barrier");
        exit(EXIT_FAILURE);
    }

    end = clock();

    double time_taken = ((double)end-start)/CLOCKS_PER_SEC;
    long minutes = (long)time_taken / 60;
    long seconds = (long)time_taken % 60;
    long milliseconds = (long)((time_taken - (long)time_taken) * 1000);

    printf("\n---------------STATISTICS--------------------\n");
    printf("Consumers: %d - Buffer Size: %d\n", numWorkers, bufferSize);
    printf("Number of Regular File: %d\n", regularFileCount);
    printf("Number of FIFO File: %d\n", fifoFileCount);
    printf("Number of Directory: %d\n", directoryCount);
    printf("TOTAL BYTES COPIED: %ld\n", totalBytesCopied);
    printf("TOTAL TIME: %02ld:%02ld.%03ld (min:sec.mili)\n", minutes, seconds, milliseconds);

    return 0;
}