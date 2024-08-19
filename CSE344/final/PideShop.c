#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <complex.h>
#include <semaphore.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define MAX_OVEN_CAPACITY 6
#define MAX_DELIVERY_CAPACITY 3
#define MAX_ORDER_COUNT 500
#define NUM_OVEN_APARATUS 3

typedef double complex Complex;

Complex matrix[30][40];
Complex transpose[40][30];
Complex product[30][30];
Complex inverse[30][30];

typedef struct {
    int order_id; // Unique identifier for the order
    int x, y; // Location of the customer
    int status; // -1: Cancelled,  0: Received, 1: Preparing, 2: Cooked, 3:Delivered
    time_t timestamp; // Time of the order
    int client_socket; // Client socket
    int pickedUp; // 0: Not picked up, 1: Picked up
} Order;

typedef struct {
    int id; // Unique identifier for the cook
    pthread_t thread; // Thread for the cook
    int busy; // 0: Free, 1: Busy
    int totalOrdersCooked; // Total number of orders cooked
} Cook;

typedef struct {
    int id; // Unique identifier for the delivery personnel
    int busy; // 0: Free, 1: Busy
    int x, y; // Location of the delivery personnel
    pthread_t thread; // Thread for the delivery personnel
    Order orders[MAX_DELIVERY_CAPACITY]; // Orders to be delivered
    int orderCount; // Number of orders to be delivered
    int deliverySpeed; // Speed of the delivery personnel
    int totalOrdersDelivered; // Total number of orders delivered
} DeliveryPersonnel;

int calculateDeliveryTime(int x, int y, int deliverySpeed, DeliveryPersonnel deliveryPersonnel);

void initializeMatrix();
void transposeMatrix();
void multiplyMatrix();
void inverseMatrix();


Order orders[MAX_ORDER_COUNT]; // Queue for the orders max 500 orders
int orderCount = 0;
Order readyOrders[MAX_ORDER_COUNT]; // Queue for the orders ready for delivery
int readyOrderCount = 0;

Cook *cooks; // Cooks
DeliveryPersonnel *deliveryPersonnel; // Delivery personnels

int serverRunning = 1;
int townX, townY; // Location of the shop
pthread_mutex_t orderLock; // Mutex for the orders
pthread_mutex_t deliveryLock; // Mutex for the delivery personnel
pthread_mutex_t readyOrderLock; // Mutex for the ready orders
pthread_cond_t orderTaken; // Condition variable for the order
int ordersLeft = 0; // Number of orders left

int cookPoolSize; // Number of cooks
int deliveryPoolSize; // Number of delivery personnel

sem_t ovenCapacity; // Semaphore for the oven capacity
sem_t ovenApparatus; // Semaphore for the oven apparatus
pthread_mutex_t ovenLock; // Mutex for the oven

pthread_cond_t orderReadyForDelivery; // Condition variable for the delivery personnel
pthread_cond_t everyOrderDelivered; // Condition variable for the delivery personnel

int server_socket; // Server socket
int totalOrders = -10; // Total number of orders
int portNumber; // Port number
FILE *logFile; // Log file
int clientPID; // Client PID


void handle_signal(int signal){
    if(signal == SIGINT){
        printf(".. Upps quiting... writing to log file\n");
        fprintf(logFile, "PideShop shutdown\n");
        serverRunning = 0;
        // signal any waiting threads
        if(pthread_cond_broadcast(&orderTaken) != 0){
            perror("pthread_cond_broadcast");
            exit(EXIT_FAILURE);
        }
        if(pthread_cond_broadcast(&orderReadyForDelivery) != 0){
            perror("pthread_cond_broadcast");
            exit(EXIT_FAILURE);
        }
        if(pthread_cond_broadcast(&everyOrderDelivered) != 0){
            perror("pthread_cond_broadcast");
            exit(EXIT_FAILURE);
        }
        close(server_socket);
    }
}

void createSocketServer(int port){
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // Create a socket
    if(server_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(portNumber);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1){ // Bind the socket to the address and port number
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server_socket, 10) == -1){ // 10 is the maximum number of clients that can be waiting while the server is busy
        perror("listen"); 
        exit(EXIT_FAILURE);
    }
}

void printBestCookAndDeliveryPersonnel(){
    int numberOfCooked = 0;
    int bestCookId = 0;
    for(int i = 0; i < cookPoolSize; i++){
        if(cooks[i].totalOrdersCooked > numberOfCooked){
            numberOfCooked = cooks[i].totalOrdersCooked;
            bestCookId = i;
        }
    }

    int numberOfDelivered = 0;
    int bestDeliveryPersonnelId = 0;
    for(int i = 0; i < deliveryPoolSize; i++){
        if(deliveryPersonnel[i].totalOrdersDelivered > numberOfDelivered){
            numberOfDelivered = deliveryPersonnel[i].totalOrdersDelivered;
            bestDeliveryPersonnelId = i;
        }
    }
    printf("Thanks Cook %d (%d orders) and Moto %d (%d deliveries)\n", bestCookId, cooks[bestCookId].totalOrdersCooked, bestDeliveryPersonnelId, deliveryPersonnel[bestDeliveryPersonnelId].totalOrdersDelivered);
}

void* managerThread(void* arg){ // Manager thread that will handle the orders    
    printf("PideShop active waiting for connection...\n");

    int firstOrder = 1;
    char repsonse[1024];
    fd_set readfds;
    struct timeval timeout; // Timeout for the select function

    while(serverRunning){
        if(orderCount == totalOrders){
            if(pthread_mutex_lock(&orderLock) != 0){
                perror("pthread_mutex_lock");
                exit(EXIT_FAILURE);
            }
            while(ordersLeft > 0){ // Wait for all orders to be delivered
                if(pthread_cond_wait(&everyOrderDelivered, &orderLock) != 0){
                    perror("pthread_cond_wait");
                    exit(EXIT_FAILURE);
                }
                if(!serverRunning){
                    break;
                }
            }
            if(ordersLeft == 0){ // All orders are delivered
                printf("Done serving client PID %d\n", clientPID);
                printBestCookAndDeliveryPersonnel();
                orderCount = 0;
                ordersLeft = 0;
                totalOrders = -10;
                firstOrder = 1;
                if(pthread_mutex_unlock(&orderLock) != 0){
                    perror("pthread_mutex_unlock");
                    exit(EXIT_FAILURE);
                }
            }
        }

        if(!serverRunning){
            break;
        }

        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int activity = select(server_socket + 1, &readfds, NULL, NULL, &timeout); // Wait for the client
        if(activity == -1){
            perror("select");
            exit(EXIT_FAILURE);
        } else if(activity == 0){
            continue;
        }

        if(FD_ISSET(server_socket, &readfds)){
            int client_socket = accept(server_socket, NULL, NULL); // Accept the client
            if(client_socket == -1){
                if(!serverRunning){
                    break;
                }
                perror("accept");
                continue;
            }

            char buffer[1024] = {0};
            int readBytes = read(client_socket, buffer, 1024); // Read the order from the client
            if(readBytes == -1){
                perror("read");
                exit(EXIT_FAILURE);
            }

            if(strncmp(buffer, "Cancel",6) == 0){
                int order_id;
                if(sscanf(buffer, "Cancel %d", &order_id) != 1){
                    perror("sscanf");
                    exit(EXIT_FAILURE);
                }
                printf("Order %d is cancelled\n", order_id);
            }

            int q,p; // Town sizes

            Order order = {0};
            if(sscanf(buffer, "Order %d: Location (%d, %d) %d Town Size (%d, %d) PID %d", &order.order_id, &order.x, &order.y, &totalOrders, &p, &q, &clientPID) != 7){
                perror("sscanf");
                exit(EXIT_FAILURE);
            }

            townX = p / 2;
            townY = q / 2;

            order.status = 0;
            order.timestamp = time(NULL);
            order.client_socket = client_socket;
            order.pickedUp = 0;

            sprintf(repsonse, "Order %d received\n", order.order_id);
            if(send(client_socket, repsonse, strlen(repsonse), 0) == -1){
                perror("send managerThread");
                exit(EXIT_FAILURE);
            }

            if(firstOrder){
                printf("%d new customers... Serving\n",totalOrders);
                firstOrder = 0;
            }

            if(pthread_mutex_lock(&orderLock) != 0){
                perror("pthread_mutex_lock");
                exit(EXIT_FAILURE);
            }

            if(orderCount < MAX_ORDER_COUNT){
                orders[orderCount++] = order;
                ordersLeft++;
                if(pthread_cond_broadcast(&orderTaken) != 0){
                    perror("pthread_cond_signal");
                    exit(EXIT_FAILURE);
                }
            } else{
                printf("Order queue is full\n");
            }

            if(pthread_mutex_unlock(&orderLock) != 0){
                perror("pthread_mutex_unlock");
                exit(EXIT_FAILURE);
            }
        }
    }
    return NULL;
}

void* cookThread(void* arg){ // Cook thread that will cook the orders
    Cook *cook = (Cook*)arg;    
    while(serverRunning){
        if(pthread_mutex_lock(&orderLock) != 0){
            perror("pthread_mutex_lock");
            // exit(EXIT_FAILURE);
            continue;
        }

        while(orderCount == 0 && serverRunning){
            if(pthread_cond_wait(&orderTaken, &orderLock) != 0){
                perror("pthread_cond_wait");
                pthread_mutex_unlock(&orderLock);
                // exit(EXIT_FAILURE);
                continue;
            }
        }

        if(!serverRunning){
            pthread_cond_broadcast(&orderReadyForDelivery);
            pthread_mutex_unlock(&orderLock);
            break;
        }

        char response[1024];
        int orderIndex = -1;
        for(int i=0; i<orderCount; ++i){
            if(orders[i].status == 0 && !cook->busy){ // If the order is received
                orders[i].status = 1; // Set the status to preparing
                orders[i].timestamp = time(NULL);
                orderIndex = i;
                cook->busy = 1; // Set the cook to busy
                break;
            }
        }
        if(orderIndex == -1){ // If no order is found
            if(pthread_mutex_unlock(&orderLock) != 0){
                perror("pthread_mutex_unlock");
                // exit(EXIT_FAILURE);
                continue;
            }
            continue;
        }
        if(pthread_mutex_unlock(&orderLock) != 0){
            perror("pthread_mutex_unlock");
            continue;
            // exit(EXIT_FAILURE);
        }

        struct timeval start, end; // Timer for preparing the order
        gettimeofday(&start, NULL); // Start the timer
        initializeMatrix();
        transposeMatrix();
        multiplyMatrix();
        inverseMatrix();
        gettimeofday(&end, NULL); // End the timer
        double time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;


        if(sem_wait(&ovenApparatus) == -1){ // Wait for the oven apparatus
            perror("sem_wait");
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }
        if(sem_wait(&ovenCapacity) == -1){ // Wait for the oven capacity
            perror("sem_wait");
            sem_post(&ovenApparatus);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        if(pthread_mutex_lock(&ovenLock) != 0){
            perror("pthread_mutex_lock");
            sem_post(&ovenApparatus);
            sem_post(&ovenCapacity);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        char timestamp[20];
        strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", localtime(&orders[orderIndex].timestamp));

        // write to log file
        if(fprintf(logFile, "(%s) Order %d prepared in %f second\n",timestamp, orders[orderIndex].order_id, time) < 0){
            perror("fprintf");
            sem_post(&ovenApparatus);
            sem_post(&ovenCapacity);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }
        
        memset(response, 0, sizeof(response));
        sprintf(response, "Order %d prepared by cook %d\n", orders[orderIndex].order_id, cook->id);
        if(send(orders[orderIndex].client_socket, response, strlen(response), 0) == -1){
            perror("send cookThread prepare");
            sem_post(&ovenApparatus);
            sem_post(&ovenCapacity);
            // exit(EXIT_FAILURE);
            continue;
        }

        if(pthread_mutex_unlock(&ovenLock) != 0){
            perror("pthread_mutex_unlock");
            sem_post(&ovenApparatus);
            sem_post(&ovenCapacity);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        if(sem_post(&ovenApparatus) == -1){ // Release the oven apparatus
            perror("sem_post");
            sem_post(&ovenCapacity);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        sleep((int)(time/2.0)); // Wait for the order to be cooked
        orders[orderIndex].status = 2; // Set the status to cooked

        if(sem_wait(&ovenApparatus) == -1){ // Wait for the oven apparatus
            perror("sem_wait");
            sem_post(&ovenCapacity);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }


        if(sem_post(&ovenCapacity) == -1){ 
            perror("sem_post");
            sem_post(&ovenApparatus);
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        if(sem_post(&ovenApparatus) == -1){ 
            perror("sem_post");
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        if(pthread_mutex_lock(&readyOrderLock) != 0){
            perror("pthread_mutex_lock");
            cook->busy = 0;
            // exit(EXIT_FAILURE);
            continue;
        }

        if (readyOrderCount < MAX_ORDER_COUNT && !orders[orderIndex].pickedUp  && orders[orderIndex].status == 2) {
            orders[orderIndex].pickedUp = 1; // Mark as picked up to avoid duplicates
            readyOrders[readyOrderCount++] = orders[orderIndex];
            // printf("Order %d is ready for delivery\n", orders[i].order_id);
            if (pthread_cond_broadcast(&orderReadyForDelivery) != 0) {
                perror("pthread_cond_signal");
                pthread_mutex_unlock(&readyOrderLock);
                cook->busy = 0;
                continue;
            }
        } else {
            printf("Ready order queue is full or order already picked up\n");
        }

        if(fprintf(logFile, "Order %d cooked\n", orders[orderIndex].order_id) < 0){
            perror("fprintf");
            cook->busy = 0;
            continue;
        }

        sprintf(response, "Order %d is cooked by cook %d\n", orders[orderIndex].order_id, cook->id);
        if(send(orders[orderIndex].client_socket, response, strlen(response), 0) == -1){
            perror("send cookThread cook");
            cook->busy = 0;
            continue;
        }

        if(pthread_mutex_unlock(&readyOrderLock) != 0){
            perror("pthread_mutex_unlock");
            cook->busy = 0;
            continue;
        }
        cook->busy = 0; // Set the cook to free
        cook->totalOrdersCooked++; // Increment the total orders cooked by the cook
    }
    return NULL;
}

void* deliveryThread(void* arg) {
    DeliveryPersonnel *deliveryPersonnel = (DeliveryPersonnel*)arg;

    deliveryPersonnel->x = townX; // Set the initial x location of the delivery personnel
    deliveryPersonnel->y = townY; // Set the initial y location of the delivery personnel

    while (serverRunning || ordersLeft > 0) {
        if (pthread_mutex_lock(&deliveryLock) != 0) {
            perror("pthread_mutex_lock");
            exit(EXIT_FAILURE);
        }

        while (readyOrderCount == 0 && serverRunning) {
            if (pthread_cond_wait(&orderReadyForDelivery, &deliveryLock) != 0) {
                perror("pthread_cond_wait");
                pthread_mutex_unlock(&deliveryLock);
                exit(EXIT_FAILURE);
            }
        }

        while ((readyOrderCount < 3 && ordersLeft > readyOrderCount) && serverRunning) {
            if (pthread_cond_wait(&orderReadyForDelivery, &deliveryLock) != 0) {
                perror("pthread_cond_wait");
                pthread_mutex_unlock(&deliveryLock);
                exit(EXIT_FAILURE);
            }
        }
        
        if (!serverRunning) {
            pthread_mutex_unlock(&deliveryLock);
            break;
        }

        int ordersToDeliver = (readyOrderCount >= 3) ? 3 : readyOrderCount;
        for(int i = 0; i < ordersToDeliver; i++){
            deliveryPersonnel->orders[i] = readyOrders[i];
            deliveryPersonnel->orders[i].pickedUp = 1;
        }

        // Shift remaining orders in the queue
        for (int i = ordersToDeliver; i < readyOrderCount; ++i) {
            readyOrders[i - ordersToDeliver] = readyOrders[i];
        }
        readyOrderCount -= ordersToDeliver;

        deliveryPersonnel->orderCount = ordersToDeliver;
        deliveryPersonnel->busy = 1;


        if(pthread_mutex_unlock(&deliveryLock) != 0){
            perror("pthread_mutex_unlock");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < deliveryPersonnel->orderCount; ++i) {
            if(!serverRunning){
                if(pthread_cond_signal(&everyOrderDelivered) != 0){ // Ensure manager thread is not stuck
                    perror("pthread_cond_broadcast");
                    exit(EXIT_FAILURE);
                }
                close(deliveryPersonnel->orders[i].client_socket);
                return NULL;
            }
            Order order = deliveryPersonnel->orders[i];

            // Calculate delivery time
            int deliveryTime = calculateDeliveryTime(order.x, order.y, deliveryPersonnel->deliverySpeed, *deliveryPersonnel);

            // Simulate delivery
            sleep(deliveryTime);

            // Update order status
            order.status = 3; // Delivered
            order.timestamp = time(NULL);

            deliveryPersonnel->x = order.x;
            deliveryPersonnel->y = order.y;


            if(fprintf(logFile, "Order %d delivered to (%d, %d) by delivery %d\n", order.order_id, order.x, order.y, deliveryPersonnel->id) < 0){
                perror("fprintf");
                exit(EXIT_FAILURE);
            }

            char response[1024];
            sprintf(response, "Order %d delivered by delivery %d\n", order.order_id, deliveryPersonnel->id);
            if(send(order.client_socket, response, strlen(response), 0) == -1){
                perror("send deliveryThread");
                exit(EXIT_FAILURE);
            }
            ordersLeft--;
            

            close(order.client_socket);

            // Update order in the global orders array
            for (int j = 0; j < orderCount; j++) {
                if (orders[j].order_id == order.order_id) {
                    orders[j] = order;
                    break;
                }
            }
        }

        // Simulate return to the shop
        sleep(1);
        deliveryPersonnel->x = townX;
        deliveryPersonnel->y = townY;


        // Update delivery statistics
        deliveryPersonnel->totalOrdersDelivered += deliveryPersonnel->orderCount;

        // Reset the order count for the next round of deliveries
        deliveryPersonnel->orderCount = 0;
        deliveryPersonnel->busy = 0;
        memset(deliveryPersonnel->orders, 0, sizeof(deliveryPersonnel->orders));
        // printf("Delivery %d returned to the shop\n", deliveryPersonnel->id);

        if(ordersLeft == 0){
            if(pthread_cond_signal(&everyOrderDelivered) != 0){
                perror("pthread_cond_broadcast");
                exit(EXIT_FAILURE);
            }
        }
    }
    return NULL;
}

int calculateDeliveryTime(int x, int y, int deliverySpeed, DeliveryPersonnel deliveryPersonnel){
    int distance = (int)sqrt(pow(deliveryPersonnel.x - x, 2) + pow(deliveryPersonnel.y - y, 2));
    int time = distance / deliverySpeed;
    return time;
}

void initializeMatrix(){
    for(int i=0; i<30; ++i){
        for(int j=0; j<40; ++j){
            double real = i + j;
            double imag = i - j;
            matrix[i][j] = real + imag * I;
        }
    }
}

void transposeMatrix(){
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 40; j++){
            transpose[j][i] = conj(matrix[i][j]);
        }
    }
}

void multiplyMatrix(){
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 30; j++){
            product[i][j] = 0;
            for(int k = 0; k < 40; k++){
                product[i][j] += matrix[i][k] * transpose[k][j];
            }
        }
    }
}

void inverseMatrix() {
    // Create an identity matrix
    Complex identity[30][30];
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            identity[i][j] = (i == j) ? 1.0 + 0.0 * I : 0.0 + 0.0 * I;
        }
    }

    // Perform Gauss-Jordan elimination
    for (int i = 0; i < 30; i++) {
        // Find maximum element in current column
        double maxEl = cabs(product[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < 30; k++) {
            if (cabs(product[k][i]) > maxEl) {
                maxEl = cabs(product[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row
        for (int k = i; k < 30; k++) {
            Complex tmp = product[maxRow][k];
            product[maxRow][k] = product[i][k];
            product[i][k] = tmp;

            tmp = identity[maxRow][k];
            identity[maxRow][k] = identity[i][k];
            identity[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < 30; k++) {
            Complex c = -product[k][i] / product[i][i];
            for (int j = i; j < 30; j++) {
                if (i == j) {
                    product[k][j] = 0;
                } else {
                    product[k][j] += c * product[i][j];
                }
                identity[k][j] += c * identity[i][j];
            }
        }
    }

    // Make all rows above this one 0 in current column
    for (int i = 29; i > 0; i--) {
        for (int k = i - 1; k >= 0; k--) {
            Complex c = -product[k][i] / product[i][i];
            for (int j = 0; j < 30; j++) {
                product[k][j] += c * product[i][j];
                identity[k][j] += c * identity[i][j];
            }
        }
    }

    // Normalize diagonal elements
    for (int i = 0; i < 30; i++) {
        Complex c = product[i][i];
        for (int j = 0; j < 30; j++) {
            product[i][j] /= c;
            identity[i][j] /= c;
        }
    }

    // Copy the identity matrix to the inverse matrix
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            inverse[i][j] = identity[i][j];
        }
    }
}

int main(int argc, char* argv[]){
    if(argc != 5){
        printf("Usage: %s [portNumber] [CookThreadPoolSize] [DeliveryPoolSize] [k]\n", argv[0]);
        return 1;
    }

    portNumber = atoi(argv[1]);
    cookPoolSize = atoi(argv[2]);
    deliveryPoolSize = atoi(argv[3]);
    int deliverySpeed = atoi(argv[4]);

    createSocketServer(portNumber); // Create the server socket

    // Signal handling
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    logFile = fopen("pideShop.log", "a");
    if(logFile == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_init(&orderLock, NULL) != 0){
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_init(&deliveryLock, NULL) != 0){
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_init(&readyOrderLock, NULL) != 0){
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_init(&orderTaken, NULL) != 0){
        perror("pthread_cond_init");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_init(&ovenLock, NULL) != 0){
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    if(sem_init(&ovenCapacity, 0, MAX_OVEN_CAPACITY) == -1){
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    if(sem_init(&ovenApparatus, 0, NUM_OVEN_APARATUS) == -1){
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_init(&orderReadyForDelivery, NULL) != 0){
        perror("pthread_cond_init");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_init(&everyOrderDelivered, NULL) != 0){
        perror("pthread_cond_init");
        exit(EXIT_FAILURE);
    }

    pthread_t manager_Thread;
    if(pthread_create(&manager_Thread, NULL, managerThread, NULL) != 0){
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    cooks = (Cook*)malloc(cookPoolSize * sizeof(Cook));
    for(int i = 0; i < cookPoolSize; i++){
        cooks[i].id = i;
        cooks[i].busy = 0;
        cooks[i].totalOrdersCooked = 0;
        pthread_create(&cooks[i].thread, NULL, cookThread, &cooks[i]);
    }
    deliveryPersonnel = (DeliveryPersonnel*)malloc(deliveryPoolSize * sizeof(DeliveryPersonnel));
    for(int i = 0; i < deliveryPoolSize; i++){
        deliveryPersonnel[i].id = i;
        deliveryPersonnel[i].busy = 0;
        deliveryPersonnel[i].orderCount = 0;
        deliveryPersonnel[i].totalOrdersDelivered = 0;
        deliveryPersonnel[i].deliverySpeed = deliverySpeed;
        pthread_create(&deliveryPersonnel[i].thread, NULL, deliveryThread, &deliveryPersonnel[i]);
    }

    // Join the threads
    if(pthread_join(manager_Thread, NULL) != 0){
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < cookPoolSize; i++){
        if(pthread_join(cooks[i].thread, NULL) != 0){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    
    for(int i = 0; i < deliveryPoolSize; i++){
        if(pthread_join(deliveryPersonnel[i].thread, NULL) != 0){
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    if(sem_destroy(&ovenCapacity) == -1){
        perror("sem_destroy");
        exit(EXIT_FAILURE);
    }

    if(sem_destroy(&ovenApparatus) == -1){
        perror("sem_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_destroy(&orderLock) != 0){
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_destroy(&deliveryLock) != 0){
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_destroy(&readyOrderLock) != 0){
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_destroy(&orderTaken) != 0){
        perror("pthread_cond_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_mutex_destroy(&ovenLock) != 0){
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_destroy(&orderReadyForDelivery) != 0){
        perror("pthread_cond_destroy");
        exit(EXIT_FAILURE);
    }

    if(pthread_cond_destroy(&everyOrderDelivered) != 0){
        perror("pthread_cond_destroy");
        exit(EXIT_FAILURE);
    }
    fclose(logFile);
    free(cooks);
    free(deliveryPersonnel);
    return 0;
}