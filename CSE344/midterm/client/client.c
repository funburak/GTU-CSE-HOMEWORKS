#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <semaphore.h>

#define SERVER_FIFO_READ "/tmp/server_%d_fifo_read" // Server FIFO for reading
#define SERVER_FIFO_WRITE "/tmp/server_%d_fifo_write" // Server FIFO for writing

#define CLIENT_FIFO_TEMPLATE_READ "/tmp/client_%d_fifo_read" // Client FIFO for reading
#define CLIENT_FIFO_TEMPLATE_WRITE "/tmp/client_%d_fifo_write" // Client FIFO for writing

#define min(a,b) ((a) < (b) ? (a) : (b))

int fd_read_client;
int fd_write_client;

void handle_server_kill(int signo) {
    if(signo == SIGUSR2){ // Special signal to handle server shutdown
        printf("Server is shutting down. Exiting...\n");
        close(fd_read_client);
        close(fd_write_client);
        exit(EXIT_SUCCESS);
    }
    else if(signo == SIGINT){
        if(write(fd_write_client, "quit", strlen("quit")) == -1){
            perror("Failed to send quit signal to server");
            close(fd_read_client);
            close(fd_write_client);
            exit(EXIT_FAILURE);
        }
        printf("Exiting...\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <Connect/tryConnect> <ServerPID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sem_t* semaphore = sem_open("/semaphore", 0);
    if (semaphore == SEM_FAILED) {
        perror("Failed to open semaphore");
        exit(EXIT_FAILURE);
    }


    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_server_kill;
    if(sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGUSR2, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    pid_t server_pid = atoi(argv[2]);
    if(kill(server_pid, 0) == -1){ // Check if server exists
        perror("Server does not exist");
        exit(EXIT_FAILURE);
    }

    char server_fifo_read[100];
    char server_fifo_write[100];
    sprintf(server_fifo_read, SERVER_FIFO_READ, server_pid);
    sprintf(server_fifo_write, SERVER_FIFO_WRITE, server_pid);

    int fd_write;
    if(strcmp(argv[1], "Connect") == 0){
        printf("Waiting for server queue...\n");
        fflush(stdout);
        if(sem_wait(semaphore) == -1){
            perror("Failed to wait on semaphore");
            exit(EXIT_FAILURE);
        }
        while((fd_write = open(server_fifo_read, O_WRONLY)) == -1){
            if(errno == ENOENT){
                continue;
            }
            else{
                perror("Failed to open server queue");
                exit(EXIT_FAILURE);
            }
        }
    }
    else if(strcmp(argv[1], "tryConnect") == 0){
        fd_write = open(server_fifo_read, O_WRONLY | O_NONBLOCK);
        if(fd_write == -1){
            perror("Failed to connect to server queue");
            exit(EXIT_FAILURE);
        }
    }


    int fd_read = open(server_fifo_write, O_RDONLY);
    if(fd_read == -1){
        perror("Failed to open fifo_write");
        exit(EXIT_FAILURE);
    }

    char request[256];
    memset(request, 0, sizeof(request));
    sprintf(request, "%d %s", getpid(), argv[1]);
    if(write(fd_write, request, strlen(request)) == -1){
        perror("Failed to write to server queue");
        exit(EXIT_FAILURE);
    }


    char response[256];
    memset(response, 0, sizeof(response));
    if(read(fd_read, response, sizeof(response)) == -1){
        perror("Failed to read from fifo_write");
        exit(EXIT_FAILURE);
    }

    if(strcmp(argv[1], "tryConnect") == 0){
        if(strcmp(response, "Full") == 0){
            printf("Server is full. Exiting...\n");
            exit(EXIT_FAILURE);
        }
    }

    char client_fifo_write[100];
    char client_fifo_read[100];
    sprintf(client_fifo_write, CLIENT_FIFO_TEMPLATE_WRITE, getpid());
    sprintf(client_fifo_read, CLIENT_FIFO_TEMPLATE_READ, getpid());

    fd_read_client = open(client_fifo_write, O_RDONLY);
    if (fd_read_client == -1) {
        perror("Failed to open client FIFO for writing");
        exit(EXIT_FAILURE);
    }

    // Open client FIFO for reading
    fd_write_client = open(client_fifo_read, O_WRONLY | O_NONBLOCK);
    if (fd_write_client == -1) {
        perror("Failed to open client FIFO for reading");
        exit(EXIT_FAILURE);
    }


    printf("Connection established\n");
    while(1){
        char command[256];
        printf("Enter command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove trailing newline

        char temp_command[256];
        strcpy(temp_command, command);
        char *token = strtok(temp_command, " ");

        if(strcmp(command,"help") == 0){
            printf("Available commands are:\n");
            printf("help, list, readF, writeT, upload, download, archServer, quit, killServer\n");
        }
        else if(strcmp(command, "help list") == 0){
            printf("list: Sends a request to display the list of files in Servers directory\n");
        }
        else if(strcmp(command, "help readF") == 0){
            printf("readF <file> <line #>: Requests to display the # line of the <file>, if no line number is given the whole contents of the file is requested\n");
        }
        else if(strcmp(command, "help writeT") == 0){
            printf("writeT <file> <line #> <string>: Request to write the content of “string” to the #th line the <file>, if the line # is not given writes to the end of file\n");
        }
        else if(strcmp(command, "help upload") == 0){
            printf("upload <file>: Uploads the file from the current working directory of client to the Servers directory\n");
        }
        else if(strcmp(command, "help download") == 0){
            printf("download <file>: Request to receive <file> from Servers directory to client side\n");
        }
        else if(strcmp(command, "help archServer") == 0){
            printf("archServer <fileName>.tar: Request to collect all the files currently available on the the Server side and store them in the <filename>.tar archive\n");
        }
        else if(strcmp(command, "help killServer") == 0){
            printf("killServer: Sends a kill request to the Server\n");
        }
        else if(strcmp(command, "help quit") == 0){
            printf("quit: Sends write request to Server side log file and quits\n");
        }
        else if(strcmp(token, "list") == 0){
            if(write(fd_write_client, "list", strlen("list")) == -1){
                perror("Failed to write to server FIFO");
                exit(EXIT_FAILURE);
            }
            printf("Request sent to server\n");

            // Wait for response from server
            char file_list[1024];
            memset(file_list, 0, sizeof(file_list));
            if (read(fd_read_client, file_list, sizeof(file_list)) == -1) {
                perror("Failed to read file list from server");
                exit(1);
            }
            printf("Files in server directory:\n%s", file_list);
        }
        else if(strcmp(token, "readF") == 0){
            char request[512];
            snprintf(request, sizeof(request), "%s", command);
            if(write(fd_write_client, request, strlen(request)) == -1){
                perror("Failed to write to server queue");
                exit(EXIT_FAILURE);
            }

            long file_size;
            if(read(fd_read_client, &file_size, sizeof(file_size)) == -1){
                perror("Failed to read from client fifo");
                exit(EXIT_FAILURE);
            }
            int bytes_read;
            long bytes_left = file_size;
            char file_content[1024];
            char buffer[1024];
            if(file_size == 8367798494427701574){ // File not found
                printf("File not found\n");
                bytes_read = read(fd_read_client, buffer, 1024);
                if(bytes_read == -1){
                    perror("Failed to read from client fifo");
                    exit(EXIT_FAILURE);
                }
                continue;
            }
            else if(file_size == 0){
                printf("Line number is out of bounds\n");
                continue;
            }
            else{
                printf("File content:\n");
                while(bytes_left > 0 && (bytes_read = read(fd_read_client, file_content, min(sizeof(file_content) - 1, bytes_left))) > 0) {
                        file_content[bytes_read] = '\0';
                        printf("%s", file_content);
                        bytes_left -= bytes_read;
                }
                if(bytes_read == -1){
                    perror("Failed to read file content from server");
                    exit(EXIT_FAILURE);
                }
                printf("\n");
            }
        }
        else if(strcmp(token,"writeT") == 0){
            char request[512];
            snprintf(request, sizeof(request), "%s", command);
            if(write(fd_write_client, request, strlen(request)) == -1){
                perror("Failed to write to server queue");
                exit(EXIT_FAILURE);
            }

            char response[512];
            memset(response, 0, sizeof(response));
            if(read(fd_read_client, response, sizeof(response)) == -1){
                perror("Failed to read from fifo_write");
                exit(EXIT_FAILURE);
            }
            printf("%s", response);
        }
        else if(strcmp(token, "upload") == 0){
            char request[512];
            snprintf(request, sizeof(request), "%s", command);
            if(write(fd_write_client, request, strlen(request)) == -1){
                perror("Failed to write to server queue");
                exit(EXIT_FAILURE);
            }
            printf("Upload request sent to server... ");


            char response[256];
            memset(response, 0, sizeof(response));
            if(read(fd_read_client, response, sizeof(response)) == -1){
                perror("Failed to read from fifo_write");
                exit(EXIT_FAILURE);
            }
            printf("Beginning file transfer:\n");
            printf("%s\n", response);
        }
        else if(strcmp(token, "download") == 0){
            char request[512];
            snprintf(request, sizeof(request), "%s", command);
            if(write(fd_write_client, request, strlen(request)) == -1){
                perror("Failed to write to server queue");
                exit(EXIT_FAILURE);
            }
            printf("Download request sent to server... ");

            char response[256];
            memset(response, 0, sizeof(response));
            if(read(fd_read_client, response, sizeof(response)) == -1){
                perror("Failed to read from fifo_write");
                exit(EXIT_FAILURE);
            }
            printf("Beginning file transfer:\n");
            printf("%s\n", response);
        }
        else if(strcmp(token, "archServer") == 0){
            char request[512];
            snprintf(request, sizeof(request), "%s", command);
            if(write(fd_write_client, request, strlen(request)) == -1){
                perror("Failed to write to server queue");
                exit(EXIT_FAILURE);
            }
            printf("Archiving the current contents of the server...\n");

            char response[1024];
            int bytes_read;
            while((bytes_read = read(fd_read_client, response, sizeof(response)-1)) > 0){
                response[bytes_read] = '\0'; // Null-terminate the string
                if(strcmp(response, "END") == 0){ // In order to prevent stucking in the loop
                    break;
                }
                printf("%s", response);
                // memset(response, 0, sizeof(response)); // Clear the buffer
            }
            if(bytes_read == -1){
                perror("Failed to read from server");
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(token, "killServer") == 0){
            if(write(fd_write_client, "killServer", strlen("killServer")) == -1){
                perror("Failed to write to server FIFO");
                exit(EXIT_FAILURE);
            }
            printf("Server kill request has been sent\n");
            printf("Exiting...\n");

            close(fd_read_client);
            close(fd_write_client);
            exit(EXIT_SUCCESS);
        }
        else if(strcmp(token, "quit") == 0){
            if(write(fd_write_client, "quit", strlen("quit")) == -1){
                perror("Failed to write to server FIFO");
                exit(EXIT_FAILURE);
            }
            printf("Exiting...\n");

            if(read(fd_read_client, response, sizeof(response)) == -1){
                perror("Failed to read from fifo_write");
                exit(EXIT_FAILURE);
            }
            printf("%s", response);

            close(fd_read_client);
            close(fd_write_client);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Invalid command. Type 'help' for list of commands\n");
        }
    }
    return 0;
}