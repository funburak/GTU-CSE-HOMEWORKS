#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define FIFO_PERM 0666

void firstChildFifo1(int numElements);
void secondChildFifo2(int numElements);

int counter = 0;

void signalHandler(int signo){
    if (signo == SIGCHLD){
        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0){
            if (WIFEXITED(status)){
                printf("Child process %d terminated with status %d\n", pid, WEXITSTATUS(status));
            }
            counter++;
        }
    }
}

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s <number> \n", argv[0]);
        return 1;
    }

    int numElements = atoi(argv[1]);
    int randomNumber[numElements];

    if (mkfifo(FIFO1, FIFO_PERM) < 0){
        perror("FIFO1 mkfifo error");
        exit(EXIT_FAILURE);
    }

    if (mkfifo(FIFO2, FIFO_PERM) < 0){
        perror("FIFO2 mkfifo error");
        exit(EXIT_FAILURE);
    }

    // Set a signal handler for SIGCHLD in the parent process to handle child process termination.
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signalHandler;
    if(sigaction(SIGCHLD, &sa, NULL) < 0){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    pid_t child1 = fork();
    if(child1 < 0){
        perror("fork child1");
        exit(EXIT_FAILURE);
    }
    else if (child1 == 0){
        firstChildFifo1(numElements);
    }

    pid_t child2 = fork();
    if(child2 < 0){
        perror("fork child2");
        exit(EXIT_FAILURE);
    }
    else if (child2 == 0){
        secondChildFifo2(numElements);
    }

    int fd1 = open(FIFO1, O_WRONLY);
    if (fd1 < 0){
        perror("open FIFO1");
        exit(EXIT_FAILURE);
    }
    int fd2 = open(FIFO2, O_WRONLY);
    if (fd2 < 0){
        perror("open FIFO2");
        exit(EXIT_FAILURE);
    }

    // Initialize random number generator
    srand(time(NULL));

    
    for (int i = 0; i < numElements; i++){
        randomNumber[i] = (rand() % 10) + 1;
        printf("Random number: %d\n", randomNumber[i]);
        if (write(fd1, &randomNumber[i], sizeof(randomNumber[i])) < 0){
            perror("write to FIFO1");
            exit(EXIT_FAILURE);
        }
        if (write(fd2, &randomNumber[i], sizeof(randomNumber[i])) < 0){
            perror("write to FIFO2");
            exit(EXIT_FAILURE);
        }
    }

    const char *command = "multiply";
    if (write(fd2, command, strlen(command)) < 0){
        perror("write command to FIFO2");
        exit(EXIT_FAILURE);
    }
    close(fd1);
    close(fd2);

    while (counter < 2){
        printf("proceeding...\n");
        sleep(2);
    }

    // Free the resources
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}

void firstChildFifo1(int numElements){
    printf("Child 1 PID: %d\n", getpid());
    sleep(10); // Sleep for 10 seconds
    int fd1 = open(FIFO1, O_RDONLY);
    if (fd1 < 0){
        perror("open fifo1 in child1");
        exit(EXIT_FAILURE);
    }
    int sum = 0, numbers;
    for (int i = 0; i < numElements; i++){
        read(fd1, &numbers, sizeof(numbers));
        sum += numbers;
    }
    printf("The sum is %d\n", sum);
    close(fd1);

    int fd2 = open(FIFO2, O_WRONLY);
    if (fd2 < 0){
        perror("open fifo2 in child1");
        exit(EXIT_FAILURE);
    }
    write(fd2, &sum, sizeof(sum));
    close(fd2);
    exit(EXIT_SUCCESS);
}

void secondChildFifo2(int numElements){
    printf("Child 2 PID: %d\n", getpid());
    sleep(10); // Sleep for 10 seconds
    int fd2 = open(FIFO2, O_RDONLY);
    if (fd2 < 0){
        perror("open fifo2 in child2");
        exit(EXIT_FAILURE);
    }
    long int product = 1;
    int numbers;
    int sum;
    for (int i = 0; i < numElements; i++){
        if(read(fd2, &numbers, sizeof(numbers)) < 0){
            perror("read from FIFO2");
            exit(EXIT_FAILURE);
        }
        product *= numbers;
    }
    printf("The product is %ld\n", product);
    sleep(5); // Sleep for 5 seconds to make sure child1 terminated
    char command[8];
    if(read(fd2, command, sizeof(command)) < 0){
        perror("read command from FIFO2");
        exit(EXIT_FAILURE);
    }
    command[strlen(command)] = '\0';
    if(read(fd2, &sum, sizeof(sum)) < 0){
        perror("read sum from FIFO2");
        exit(EXIT_FAILURE);
    }
    if (strcmp(command, "multiply") == 0){
        printf("The final result is %ld\n", product + sum);
        close(fd2);
        exit(EXIT_SUCCESS);
    }
    close(fd2);
    exit(EXIT_FAILURE);
}
