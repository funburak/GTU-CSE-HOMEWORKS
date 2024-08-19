#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int numberOfClients;
int clientRunning = 1;

int *client_sockets;

void handle_signal(int signal){
    if(signal == SIGINT){
        printf("signal... cancelling orders... editing log\n");

        for(int i=0; i<numberOfClients; i++){
            char buffer[1024] = {0};
            sprintf(buffer, "Cancel %d", i+1);
            if(send(client_sockets[i], buffer, strlen(buffer), 0) < 0){
                perror("send");
                exit(EXIT_FAILURE);
            }
        }

        for(int i=0; i<numberOfClients; i++){
            close(client_sockets[i]);
        }
        // exit(EXIT_SUCCESS);
    }
}

void send_order(int sock, int order_id, int x, int y, int townX, int townY) {
    char buffer[1024] = {0};
    sprintf(buffer, "Order %d: Location (%d, %d) %d Town Size (%d, %d) PID %d", order_id, x, y, numberOfClients, townX, townY, getpid());
    if(send(sock, buffer, strlen(buffer), 0) < 0){
        perror("send");
        exit(EXIT_FAILURE);
    }
}

void* handle_client(void* arg){
    int sock = *(int*)arg;
    char response[1024] = {0};  
    while(clientRunning){
        if(!clientRunning){
            break;
        }
        memset(response, 0, sizeof(response));
        ssize_t len = recv(sock, response, sizeof(response), 0);
        if(len < 0){
            perror("recv");
            exit(EXIT_FAILURE);
        } else if(len == 0){
            break;
        }
        response[len] = '\0';
        printf("%s", response);
    }
    free(arg); // free the memory allocated in main
    return NULL;
}

int main(int argc, char const *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s [ip] [portnumber] [numberOfClients] [p] [q]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);
    numberOfClients = atoi(argv[3]);
    int p = atoi(argv[4]);
    int q = atoi(argv[5]);

    srand(time(NULL));

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_signal;
    if(sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[numberOfClients];
    client_sockets = (int*)malloc(sizeof(int) * numberOfClients);

    printf("PID: %d\n", getpid());

    for (int i = 0; i < numberOfClients; i++) {
        int *sock = (int*)malloc(sizeof(int));
        if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("Socket creation error\n");
            return -1;
        }

        client_sockets[i] = *sock;

        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
            printf("Invalid address/ Address not supported\n");
            return -1;
        }

        if (connect(*sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Connection Failed");
            return -1;
        }

        int x = rand() % p;
        int y = rand() % q;
        send_order(*sock, i + 1, x, y, p, q);

        if(pthread_create(&threads[i], NULL, handle_client, sock) != 0){
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        sleep(1); // wait for the server to process the order
    }

    for(int i = 0; i < numberOfClients; i++){
        pthread_join(threads[i], NULL);
    }

    free(client_sockets);

    printf("All customers served\n");
    return 0;
}