#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/wait.h>

#define SERVER_FIFO_READ "/tmp/server_%d_fifo_read" // Server main fifo for receiving connection requests
#define SERVER_FIFO_WRITE "/tmp/server_%d_fifo_write" // Server main fifo for sending  connection status

#define CLIENT_FIFO_TEMPLATE_READ "/tmp/client_%d_fifo_read" // Client fifo for reading commands
#define CLIENT_FIFO_TEMPLATE_WRITE "/tmp/client_%d_fifo_write" // Client fifo for writing responses


int fd_server_read; // server main fifo for receiving connection requests
int fd_server_write; // server main fifo for sending connection status
int server_log_fd; // server log file
int* client_fds; // file descriptors for client fifo's
int* client_pids; // client pid's
pid_t* child_pids; // child pid's
sem_t* semaphore; // semaphore for handling client connections
int child_count; // number of child processes
int client_count = 0; // number of connected clients
pid_t parent_pid; // parent pid
char* dirname; // server directory
int connected_clients = 0; // number of connected clients

void handle_signal(int sig) {
    if(sig == SIGUSR1 || sig == SIGINT){
        if(sig == SIGINT){
            if (getpid() == parent_pid) {
                printf(">>Received signal %d, terminating...\n>>bye\n", sig);
                char log_buffer[256];
                memset(log_buffer, 0, sizeof(log_buffer));
                sprintf(log_buffer, "Received signal %d, terminating...\n", sig);
                if(write(server_log_fd, log_buffer, strlen(log_buffer)) == -1){
                    perror("Failed to write to server log file");
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Send kill signal to child processes
        for (int i = 0; i < child_count; i++) {
            kill(child_pids[i], SIGUSR2);
        }

        // send kill signal to clients and remove client FIFO's
        for (int i = 0; i < client_count; i++) {
            char client_fifo_write[100];
            char client_fifo_read[100];
            sprintf(client_fifo_write, CLIENT_FIFO_TEMPLATE_WRITE, client_pids[i]);
            sprintf(client_fifo_read, CLIENT_FIFO_TEMPLATE_READ, client_pids[i]);
            unlink(client_fifo_write);
            unlink(client_fifo_read);
            close(client_fds[i]);
            kill(client_pids[i], SIGUSR2);
        }
        
        // remove server FIFO's
        char server_fifo_read[100];
        char server_fifo_write[100];
        sprintf(server_fifo_read, SERVER_FIFO_READ, getpid());
        sprintf(server_fifo_write, SERVER_FIFO_WRITE, getpid());
        unlink(server_fifo_read);
        unlink(server_fifo_write);

        // release semaphore
        sem_close(semaphore);
        sem_unlink("/semaphore");
        
        // Close server fifo file descriptors
        close(fd_server_write);
        close(fd_server_read);

        
        if(close(server_log_fd) == -1){ // Close server log file
            perror("Failed to close server log file");
            exit(EXIT_FAILURE);
        }

        // Clean up resources
        free(client_pids);
        free(client_fds);
        free(child_pids);

        exit(EXIT_SUCCESS);
    }
}


void handle_child_signal(int sig) { // handling when any child process in server terminates
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < child_count; i++) { 
            if (child_pids[i] == pid) {
                for (int j = i; j < child_count - 1; j++) {
                    child_pids[j] = child_pids[j + 1];
                }
                child_count--;
                break;
            }
        }
    }
    // if(sem_post(semaphore) == -1){
    //     perror("Failed to post semaphore");
    //     exit(EXIT_FAILURE);
    // }
}

void execute_command(char* command, int fd_write_client, int client_id, int client_pid){
    char* filename;
    char response[256];
    memset(response, 0, sizeof(response));
    if(strcmp(command,"list") == 0){
        DIR *dir;
        struct dirent *entry;
        struct stat statbuf;
        dir = opendir(dirname);  // Open the current directory
        if (dir == NULL) {
            sprintf(response, "Failed to open directory.\n");
        } else {
            strcpy(response, "");  // Clear the response
            char file_path[261];
            while ((entry = readdir(dir)) != NULL) {
                sprintf(file_path, "%s/%s", dirname,entry->d_name); // Get the full path of the entry
                stat(file_path, &statbuf); // Get the stats of the entry
                if (S_ISREG(statbuf.st_mode)) { // If the entry is a regular file
                    strcat(response, entry->d_name);
                    strcat(response, "\n");
                }
            }
            if(strlen(response) == 0){
                sprintf(response, "No files in directory.\n");
            }
            closedir(dir);
        }
        if(write(fd_write_client, response, strlen(response)) == -1){
            perror("Failed to write to client fifo");
            exit(EXIT_FAILURE);
        }
    }
    else if(strncmp(command, "readF", 5) == 0){
        char file_buffer[1024];
        int line_number = -1;
        long content_size = 0;
        filename = strtok(command + 5, " ");
        char *line_str = strtok(NULL, " ");
        if(line_str != NULL){
            line_number = atoi(line_str) - 1;
        }
        char path[512];
        sprintf(path, "%s/%s", dirname,filename);
        FILE *file = fopen(path, "r");
        if(file == NULL) {
            sprintf(response, "Failed to open file: %s\n", filename);
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
        }else{
            if(flock(fileno(file), LOCK_EX) != 0){
                sprintf(response, "File is locked by another client.\n");
                if(write(fd_write_client,response, strlen(response)) < 0){
                    perror("Failed to write to client fifo");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                if(line_number == -1) {
                    // If no line number is given, send the whole file
                    fseek(file, 0, SEEK_END);
                    content_size = ftell(file); // Get the property of the file
                    rewind(file); // Reset file pointer to the beginning
                    if(write(fd_write_client, &content_size, sizeof(content_size)) < 0){
                        perror("Failed to write to client fifo");
                        exit(EXIT_FAILURE);
                    }
                    while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
                        if(write(fd_write_client, file_buffer, strlen(file_buffer)) < 0){
                            perror("Failed to write to client fifo");
                            exit(EXIT_FAILURE);
                        }
                    }
                } else { // If a line number is given
                    char temp_buffer[1024];
                    int total_lines = 0;
                    while(fgets(temp_buffer, sizeof(temp_buffer), file) != NULL){ // Count the total number of lines in the file
                        total_lines++;
                    }
                    rewind(file); // Reset file pointer to the beginning

                    if(line_number > total_lines - 1){ // If the line number is out of bounds
                        content_size = 0;
                        if(write(fd_write_client, &content_size, sizeof(content_size)) < 0){
                            perror("Failed to write to client fifo");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else{
                        int current_line = 0;
                        while (fgets(file_buffer, sizeof(file_buffer), file) != NULL) {
                            if (current_line == line_number){
                                long content_size = strlen(file_buffer);
                                if(write(fd_write_client, &content_size, sizeof(content_size))<0){
                                    perror("Failed to write to client fifo");
                                    exit(EXIT_FAILURE);
                                }
                                if(write(fd_write_client, file_buffer, content_size) < 0){
                                    perror("Failed to write to client fifo");
                                    exit(EXIT_FAILURE);
                                }
                                break;
                            }
                            current_line++;
                        }
                        flock(fileno(file), LOCK_UN);
                    }
                }
            }
            fclose(file);
            return;
        }
    }
    else if(strncmp(command, "writeT", 6) == 0){
        filename = strtok(command + 6, " ");
        int line_number = -1;
        char *line_str = strtok(NULL, " ");
        char* string = strtok(NULL, "\n");
        if(string == NULL){ // This means no line number is given
            string = line_str;
            line_str = NULL;
        }
        if(line_str != NULL){
            line_number = atoi(line_str);
            if(line_number == 0){ // If line number is 0, increment it by 1
                line_number++;
            }
        }
        if(string == NULL && line_str == NULL){ // If no string is given
            sprintf(response, "No string given.\n");
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
            return;
        }
        char path[512];
        sprintf(path, "%s/%s", dirname,filename);

        FILE *file = fopen(path, "a+");
        if(file == NULL){
            sprintf(response, "Failed to open file: %s\n", filename);
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
        }
        else{
            if(flock(fileno(file), LOCK_EX) != 0){
                sprintf(response, "File is locked by another client.\n");
                if(write(fd_write_client, response, strlen(response)) < 0){
                    perror("Failed to write to client fifo");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                if(line_number == -1){ // Append to the end of the file if no line number is given
                    fputs(string, file);
                    fputs("\n", file);

                }
                else{
                    // Write to a specific line
                    char temp_file[512];
                    sprintf(temp_file, "%s/%s.tmp", dirname, filename);
                    FILE *temp = fopen(temp_file, "w");
                    if(temp == NULL){
                        sprintf(response,"Failed to open temporary file.\n");
                        if(write(fd_write_client, response, strlen(response)) < 0){
                            perror("Failed to write to client fifo");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else{
                        int current_line = 1;
                        char file_buffer[1024];
                        while(fgets(file_buffer, sizeof(file_buffer), file) != NULL){
                            if(current_line == line_number){
                                fputs(string, temp);
                                fputs("\n", temp);
                            }
                            else{
                                fputs(file_buffer, temp);
                            }
                            current_line++;
                        }
                        if(current_line <= line_number){
                            fputs(string, temp);
                            fputs("\n", temp);
                        }
                        fclose(temp);
                        rename(temp_file, path);
                    }
                }
                sprintf(response,"Write successful\n");
                if(write(fd_write_client, response, strlen(response)) < 0){
                    perror("Failed to write to client fifo");
                    exit(EXIT_FAILURE);
                }
                flock(fileno(file), LOCK_UN);
            }
            fclose(file);
            return;
        }
    }
    else if(strncmp(command, "upload", 6) == 0){
        filename = strtok(command + 6," ");
        char clientPath[512];
        sprintf(clientPath, "../client/%s", filename); // Path to the file in the client directory

        struct stat fileChecker; // Struct to check if file exists
        if(stat(clientPath, &fileChecker) == -1){ // Check if file exists
            sprintf(response, "File does not exist.\n");
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
            return;
        }
        else if(S_ISDIR(fileChecker.st_mode)){ // Check if file is a directory
            sprintf(response, "Cannot upload a directory.\n");
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
            return;
        }
        else{
            char path[512];
            sprintf(path, "%s/%s", dirname, filename);
            if(access(path, F_OK) != -1){ // Check if file already exists in the server directory
                sprintf(response, "File already exists.\n");
                if(write(fd_write_client, response, strlen(response)) < 0){
                    perror("Failed to write to client fifo");
                    exit(EXIT_FAILURE);
                }
                return;
            }
            else{
                FILE *source = fopen(clientPath, "rb");
                if(source == NULL){
                    sprintf(response, "Failed to open source file\n");
                    if(write(fd_write_client, response, strlen(response)) < 0){
                        perror("Failed to write to client fifo");
                        exit(EXIT_FAILURE);
                    }
                    return;
                }
                else{
                    FILE* dest = fopen(path, "wb");
                    if(dest == NULL){
                        sprintf(response,"Failed to open destination file\n");
                        if(write(fd_write_client, response, strlen(response)) < 0){
                            perror("Failed to write to client fifo");
                            exit(EXIT_FAILURE);
                        }
                        return;
                    }
                    else{
                        char buffer[1024];
                        ssize_t bytes;
                        ssize_t total_bytes = 0;

                        while((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0){
                            fwrite(buffer, 1, bytes, dest);
                            total_bytes += bytes;
                        }
                        fclose(source);
                        fclose(dest);
                        sprintf(response, "Upload successful. %ld bytes transferred.\n", total_bytes);
                        if(write(fd_write_client, response, strlen(response)) < 0){
                            perror("Failed to write to client fifo");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
        }
    }
    else if(strncmp(command, "download", 8) == 0){
        filename = strtok(command + 8, " ");

        char path[512];
        sprintf(path, "%s/%s", dirname, filename);

        struct stat fileChecker;
        if(stat(path, &fileChecker) == -1){
            sprintf(response, "File does not exist.\n");
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
            return;
        }
        else if(S_ISDIR(fileChecker.st_mode)){
            sprintf(response, "Cannot download a directory.\n");
            if(write(fd_write_client, response, strlen(response)) < 0){
                perror("Failed to write to client fifo");
                exit(EXIT_FAILURE);
            }
            return;
        }
        else{
            FILE *source = fopen(path, "rb");
            if(source == NULL){
                sprintf(response, "Failed to open file.\n");
                if(write(fd_write_client, response, strlen(response)) < 0){
                    perror("Failed to write to client fifo");
                    exit(EXIT_FAILURE);
                }
                return;
            }
            else{
                char client_destination[512];
                sprintf(client_destination, "../client/%s", filename);
                FILE *dest = fopen(client_destination, "wb");
                if(dest == NULL){
                    sprintf(response, "Failed to open destination file.\n");
                    if(write(fd_write_client, response, strlen(response)) < 0){
                        perror("Failed to write to client fifo");
                        exit(EXIT_FAILURE);
                    }
                    return;
                }
                else{
                    char buffer[1024];
                    ssize_t bytes;
                    ssize_t total_bytes = 0;
                    while((fgets(buffer, sizeof(buffer), source)) != NULL){
                        fwrite(buffer, 1, strlen(buffer), dest);
                        total_bytes += strlen(buffer);
                    }
                    fclose(source);
                    fclose(dest);
                    sprintf(response, "Download successful. %ld bytes transferred.\n", total_bytes);
                    if(write(fd_write_client, response, strlen(response)) < 0){
                        perror("Failed to write to client fifo");
                        exit(EXIT_FAILURE);
                    }
                }
            }
        }
    }
    else if(strncmp(command, "archServer", 10) == 0){
        char response[1024];
        char *filename = strtok(command + 10, " ");
        if (!filename) {
            perror("Filename not provided");
            exit(EXIT_FAILURE);
        }

        char path[256];
        sprintf(path, "%s",filename); // Create the tar file in the server directory

        sprintf(response, "Creating archive directory\n");
        if(write(fd_write_client, response, strlen(response)) < 0) {
            perror("Failed to write to client");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("Failed to fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            char tar_command[512];
            sprintf(tar_command, "tar -cf %s -C %s .", path, dirname); // Tar the server directory
            sprintf(response,"Calling tar utility... child PID %d\n", getpid());
            if(write(fd_write_client, response, strlen(response)) < 0) {
                perror("Failed to write to client");
                exit(EXIT_FAILURE);
            }
            execl("/bin/sh", "sh", "-c", tar_command, (char *)NULL);
            perror("Failed to execute tar");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                memset(response, 0, sizeof(response)); // Clear the response
                sprintf(response, "child returned with SUCCESS...\n");
                if (write(fd_write_client, response, strlen(response)) < 0) {
                    perror("Failed to write to client");
                    exit(EXIT_FAILURE);
                }

                char client_path[256];
                sprintf(client_path, "../client/%s", filename); // Create the tar file in the client directory
                FILE *source = fopen(path, "rb");
                if (source == NULL) {
                    perror("Failed to open file");
                    exit(EXIT_FAILURE);
                }
                FILE *dest = fopen(client_path, "wb");
                if (dest == NULL) {
                    perror("Failed to open file");
                    exit(EXIT_FAILURE);
                }

                memset(response, 0, sizeof(response)); // Clear the response
                sprintf(response, "Copying the archive file..\n");
                if (write(fd_write_client, response, strlen(response)) < 0) {
                    perror("Failed to write to client");
                    exit(EXIT_FAILURE);
                }

                char buffer[1024];
                ssize_t bytes;
                ssize_t total_bytes = 0;
                while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
                    fwrite(buffer, 1, bytes, dest);
                    total_bytes += bytes;
                }
                fclose(source);
                fclose(dest);

                memset(response, 0, sizeof(response)); // Clear the response
                sprintf(response,"Removing the archive file..\n");
                if(write(fd_write_client, response, strlen(response)) < 0){
                    perror("Failed to write to client");
                    exit(EXIT_FAILURE);
                }

                if(remove(path) == -1){
                    perror("Failed to remove tar file");
                    exit(EXIT_FAILURE);
                }

                memset(response, 0, sizeof(response)); // Clear the response
                sprintf(response, "Archive successful in %s %ld bytes transferred.\n", client_path,total_bytes);
                if (write(fd_write_client, response, strlen(response)) < 0) {
                    perror("Failed to write to client");
                    exit(EXIT_FAILURE);
                }


                memset(response, 0, sizeof(response)); // Clear the response
                sprintf(response, "END");
                if (write(fd_write_client, response, strlen(response)) < 0) {
                    perror("Failed to write to client");
                    exit(EXIT_FAILURE);
                }

            } else {
                memset(response, 0, sizeof(response)); // Clear the response
                sprintf(response, "Archive failed.\n");
                if (write(fd_write_client, response, strlen(response)) < 0) {
                    perror("Failed to write to client");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    else if(strcmp(command, "killServer") == 0){
        sprintf(response, "Server is shutting down.\n");
        if(write(fd_write_client, response, strlen(response)) < 0){
            perror("Failed to write to client fifo");
            exit(EXIT_FAILURE);
        }

        printf("Kill signal from client%d.. terminating...\n", client_id);
        printf("Bye!\n");
        kill(getppid(), SIGUSR1);
    }
    else if(strcmp(command, "quit") == 0){
        sprintf(response, "Goodbye!\n");
        if(write(fd_write_client, response, strlen(response)) < 0){
            perror("Failed to write to client fifo");
            exit(EXIT_FAILURE);
        }

        printf("Client%d disconnected\n", client_id);

        connected_clients--;

        char client_fifo_write[100];
        char client_fifo_read[100];
        sprintf(client_fifo_write, CLIENT_FIFO_TEMPLATE_WRITE, client_pid);
        sprintf(client_fifo_read, CLIENT_FIFO_TEMPLATE_READ, client_pid);
        unlink(client_fifo_write);
        unlink(client_fifo_read);

        close(fd_write_client);

        if(sem_post(semaphore) == -1){
            perror("Failed to post semaphore");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else{
        sprintf(response, "Invalid command\n");
        if(write(fd_write_client, response, strlen(response)) < 0){
            perror("Failed to write to client fifo");
            exit(EXIT_FAILURE);
        }
    }
}


int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: %s <dirname> <max. # of clients>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int max_clients = atoi(argv[2]);
    dirname = argv[1];
    parent_pid = getpid();

    struct sigaction sa;

    client_pids = (int*)malloc(max_clients * sizeof(int));
    client_fds = (int*)malloc(max_clients * sizeof(int));
    child_pids = (pid_t*)malloc(max_clients * sizeof(pid_t));

    if(mkdir(argv[1], 0777) == -1){
        if(errno != EEXIST){
            perror("Failed to create directory");
            exit(EXIT_FAILURE);
        }
    }

    sem_unlink("/semaphore"); // Unlink semaphore if it already exists
    semaphore = sem_open("/semaphore", O_CREAT | O_EXCL, 0777, max_clients);
    if(semaphore == SEM_FAILED){
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    // if(sem_init(semaphore, 0, max_clients) == -1){
    //     perror("Failed to initialize semaphore");
    //     exit(EXIT_FAILURE);
    // }

    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGUSR1, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }


    sa.sa_handler = handle_child_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Restart system calls if interrupted
    if(sigaction(SIGCHLD, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf(">> Server started PID %d...\n", getpid());

    char server_fifo_read[100];
    char server_fifo_write[100];
    sprintf(server_fifo_read, SERVER_FIFO_READ, getpid());
    sprintf(server_fifo_write, SERVER_FIFO_WRITE, getpid());


    if(mkfifo(server_fifo_read, 0666) < 0){
        if(errno == EEXIST){
            unlink(server_fifo_read);
            if(mkfifo(server_fifo_read, 0666) < 0){
                perror("Failed to create server read fifo");
                exit(EXIT_FAILURE);
            }
        }
        else{
            perror("Failed to create server read fifo");
            exit(EXIT_FAILURE);
        }
    }


    if(mkfifo(server_fifo_write, 0666) < 0){
        if(errno == EEXIST){
            unlink(server_fifo_write);
            if(mkfifo(server_fifo_write, 0666) < 0){
                perror("Failed to create server fifo write");
                exit(EXIT_FAILURE);
            }
        }
        else{
            perror("Failed to create server fifo write");
            exit(EXIT_FAILURE);
        }
    }

    fd_server_read = open(server_fifo_read, O_RDWR);
    if(fd_server_read == -1){
        perror("Failed to open server fifo read");
        exit(EXIT_FAILURE);
    }

    fd_server_write = open(server_fifo_write, O_RDWR);
    if(fd_server_write == -1){
        perror("Failed to open server fifo write");
        exit(EXIT_FAILURE);
    }

    server_log_fd = open("serverlog.txt", O_CREAT | O_RDWR | O_APPEND, 0666);
    if(server_log_fd == -1){
        perror("Failed to open server log file");
        exit(EXIT_FAILURE);
    }


    printf(">> Waiting for clients...\n");

    while(1){
        char buf[100] = {0};
        int num_read = read(fd_server_read, buf, sizeof(buf));
        if(num_read == -1){
            perror("Failed to read from fifo_read");
            exit(EXIT_FAILURE);
        }
        buf[num_read] = '\0';

        int client_pid;
        char command[100];
        memset(command, 0, sizeof(command));

        char *token;

        // Get the first token (client_pid)
        token = strtok(buf, " ");
        if (token == NULL) {
            // Handle error
        }
        client_pid = atoi(token);

        // Get the second token (command)
        token = strtok(NULL, " ");
        if (token == NULL) {
            // Handle error
        }
        strcpy(command, token);

        // sscanf(buf, "%d %s", &client_pid, command);

        if(client_pid == -1){
            if(errno == EINTR){
                continue;
            }
            else{
                perror("Failed to read from fifo_write");
                exit(EXIT_FAILURE);
            }
        }
        else if(client_pid == 0){
            break;
        }

        int connect_status = 0;
        if(connected_clients >= max_clients){
            if(strcmp(command, "tryConnect") == 0){
                printf(">> Connection request PID %d.. Queue Full\n", client_pid);
                if(write(fd_server_write, "Full", strlen("Full")) == -1){
                    perror("Failed to write to server queue");
                    exit(EXIT_FAILURE);
                }
                char log_buffer[256];
                memset(log_buffer, 0, sizeof(log_buffer));
                sprintf(log_buffer, "Connection request PID %d.. Queue Full\n", client_pid);
                if(write(server_log_fd, log_buffer, strlen(log_buffer)) == -1){
                    perror("Failed to write to server log file");
                    exit(EXIT_FAILURE);
                }
            }
            else if (strcmp(command,"Connect") == 0) {
                printf("Connection request PID %d.. Queue Full\n", client_pid);
                connect_status = 1;
            }
        }
        if(connected_clients < max_clients || connect_status){
            printf(">> Client PID %d connected as client%d\n", client_pid, client_count+1);
            connected_clients++;

            char log_buffer[256];
            memset(log_buffer, 0, sizeof(log_buffer));
            sprintf(log_buffer, "Client PID %d connected as client%d\n", client_pid, client_count+1);   
            if(write(server_log_fd,log_buffer,strlen(log_buffer)) == -1){
                perror("Failed to write to server log file");
                exit(EXIT_FAILURE);
            }

            client_pids[client_count++] = client_pid;

            char client_fifo_write[100];
            char client_fifo_read[100];
            sprintf(client_fifo_write, CLIENT_FIFO_TEMPLATE_WRITE, client_pid);
            sprintf(client_fifo_read, CLIENT_FIFO_TEMPLATE_READ, client_pid);

            if(mkfifo(client_fifo_write,0666) < 0){
                if(errno == EEXIST){
                    unlink(client_fifo_write);
                    if(mkfifo(client_fifo_write,0666) < 0){
                        perror("Failed to create client write fifo");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    perror("Failed to create client write fifo");
                    exit(EXIT_FAILURE);
                }
            }

            if(mkfifo(client_fifo_read,0666) < 0){
                if(errno == EEXIST){
                    unlink(client_fifo_read);
                    if(mkfifo(client_fifo_read,0666) < 0){
                        perror("Failed to create client read fifo");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    perror("Failed to create client read fifo");
                    exit(EXIT_FAILURE);
                }   
            }

            int fd_write_client = open(client_fifo_write, O_RDWR);
            if(fd_write_client == -1){
                perror("Failed to open client write fifo");
                exit(EXIT_FAILURE);
            }

            int fd_read_client = open(client_fifo_read, O_RDWR);
            if(fd_read_client == -1){
                perror("Failed to open client read fifo");
                exit(EXIT_FAILURE);
            }

            pid_t child = fork();
            if(child == -1){
                perror("Failed to fork");
                exit(EXIT_FAILURE);
            }
            else if(child == 0){ // Child process to handle client commands
                int client_id = client_count;
                char response[256];
                sprintf(response,"Status 1");
                if(write(fd_server_write, response, strlen(response)) == -1){
                    perror("Failed to write to server queue");
                    exit(EXIT_FAILURE);
                }
                while(1){
                    int num_read = read(fd_read_client, buf, sizeof(buf));
                    if(num_read <= 0){
                        break;
                    }
                    buf[num_read] = '\0';

                    char log_buffer[256];
                    memset(log_buffer, 0, sizeof(log_buffer));
                    sprintf(log_buffer, "Client%d command: %s\n", client_id, buf);
                    if(write(server_log_fd, log_buffer, strlen(log_buffer)) == -1){
                        perror("Failed to write to server log file");
                        exit(EXIT_FAILURE);
                    }

                    execute_command(buf,fd_write_client,client_id,client_pid);
                }
                exit(EXIT_SUCCESS);
            }
            else{
                if(child_count < max_clients){
                    client_fds[child_count] = fd_write_client;
                    child_pids[child_count++] = child;
                }
                continue;
            }
        }
    }
    return 0;
}