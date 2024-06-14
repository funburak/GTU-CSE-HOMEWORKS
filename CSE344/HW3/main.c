#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define AUTOMOBILE_TEMP_SPOTS 8
#define PICKUP_TEMP_SPOTS 4

// Semaphores
sem_t newPickup, newAutomobile;
sem_t inChargeforPickup, inChargeforAutomobile;
pthread_mutex_t newCar;

// Counters for free spots
int mFree_automobile = AUTOMOBILE_TEMP_SPOTS;
int mFree_pickup = PICKUP_TEMP_SPOTS;

void* carOwner(void* arg) {
    sleep((rand() % 10) + 4); // Random time for car to arrive
    srand(time(NULL) + pthread_self()); // Seed for random number generator
    int vehicleType =  rand() % 2; // 0 for pickup, 1 for automobile

    // To handle only one car can enter the parking system at a time
    if(pthread_mutex_lock(&newCar) != 0){
        perror("pthread_mutex_lock");
        return NULL;
    }

    if(vehicleType == 0){ // Pickup
        // printf("Car owner: Pickup arriving at the parking lot.\n");
        if(mFree_pickup <= 0){
            printf("No space for pickup. Leaving...\n");
            if(pthread_mutex_unlock(&newCar) != 0){
                perror("pthread_mutex_unlock");
                return NULL;
            }
            return NULL;
        }
        else{
            if(sem_wait(&newPickup) != 0){
                perror("sem_wait");
                return NULL;
            }
            mFree_pickup--;
            printf("Car owner: Pickup parked in temporary space. Remaining temporary spots: %d\n", mFree_pickup);
            if(sem_post(&inChargeforPickup) != 0){
                perror("sem_post");
                return NULL;
            }
        }
    }
    else if(vehicleType == 1){ // Automobile
        // printf("Car owner: Automobile arriving at the parking lot.\n");
        if(mFree_automobile <= 0){
            printf("No space for automobile. Leaving...\n");
            if(pthread_mutex_unlock(&newCar) != 0){
                perror("pthread_mutex_unlock");
                return NULL;
            }
            return NULL;
        }
        else{
            if(sem_wait(&newAutomobile) != 0){
                perror("sem_wait");
                return NULL;
            }
            mFree_automobile--;
            printf("Car owner: Automobile parked in temporary space. Remaining temporary spots: %d\n", mFree_automobile);
            if(sem_post(&inChargeforAutomobile) != 0){
                perror("sem_post");
                return NULL;
            }
        }
    }
    if(pthread_mutex_unlock(&newCar) != 0){
        perror("pthread_mutex_unlock");
        return NULL;
    }
    return NULL;
}

void* carAttendant(void* arg) {
    int carType = *((int*)arg);
    while(1){
        sleep((rand() % 5) + 1); // Random time for car to be parked
        if(carType == 0){ // Pickup
            if(sem_wait(&inChargeforPickup) != 0){
                perror("sem_wait");
                return NULL;
            }
            if(mFree_pickup >= PICKUP_TEMP_SPOTS){ // After all temporary spots are free, break the loop
                break;
            }
            mFree_pickup++;
            printf("Car attendant: Pickup has been parked in the final spot. Remaining temporary spots: %d\n", mFree_pickup);
            if(sem_post(&newPickup) != 0){
                perror("sem_post");
                return NULL;
            }
        }
        else if(carType == 1){ // Automobile
            if(sem_wait(&inChargeforAutomobile) != 0){
                perror("sem_wait");
                return NULL;
            }
            if(mFree_automobile >= AUTOMOBILE_TEMP_SPOTS){ // After all temporary spots are free, break the loop
                break;
            }
            mFree_automobile++;
            printf("Car attendant: Automobile has been parked in the final spot. Remaining temporary spots: %d\n", mFree_automobile);
            if(sem_post(&newAutomobile) != 0){
                perror("sem_post");
                return NULL;
            }
        }
    }
    return NULL;
}

int main() {
    pthread_t carOwners[20]; // Car owners
    pthread_t valetForPickup, valetForAutomobile; // 2 valets

    // Initialize semaphores and mutex
    if(sem_init(&newPickup, 0, PICKUP_TEMP_SPOTS) != 0 ||
        sem_init(&newAutomobile, 0, AUTOMOBILE_TEMP_SPOTS) != 0 ||
        sem_init(&inChargeforPickup, 0, 0) != 0 ||
        sem_init(&inChargeforAutomobile, 0, 0) != 0 ||
        pthread_mutex_init(&newCar, NULL) != 0){
            perror("Initilazation failed");
            return 1;
    }

    printf("#######################################################\n");
    printf("#               Welcome to the parking lot!           #\n");
    printf("#######################################################\n");

    // Create two different attendant threads for the two different types of cars
    int pickup = 0, automobile = 1;
    if(pthread_create(&valetForPickup, NULL, carAttendant, &pickup) != 0 ||
        pthread_create(&valetForAutomobile, NULL, carAttendant, &automobile) != 0){
        perror("pthread_create for vallets failed");
        return 1;
    }

    // Create threads for car owners
    for(int i = 0; i < 20; i++){
        if(pthread_create(&carOwners[i], NULL, carOwner, NULL) != 0){
            perror("pthread_create for car owners failed");
            return 1;
        }
    }

    // Wait for all threads to finish
    for(int i = 0; i < 20; i++){
        if(pthread_join(carOwners[i], NULL) != 0){
            perror("pthread_join failed");
            return 1;
        }
    }


    // Handle remaining cars in the temporary parking lot
    int remainingPickupCars = PICKUP_TEMP_SPOTS - mFree_pickup;
    printf("Remaining pickups in temporary parking lot: %d\n", remainingPickupCars);
    int remainingAutomobileCars = AUTOMOBILE_TEMP_SPOTS - mFree_automobile;
    printf("Remaining automobiles in temporary parking lot: %d\n", remainingAutomobileCars);

    while(remainingPickupCars > 0 || remainingAutomobileCars > 0){
        if(remainingPickupCars >= 0){
            if(sem_post(&inChargeforPickup) != 0){
                perror("sem_post");
                return 1;
            }
            remainingPickupCars--;
        }
        if(remainingAutomobileCars >= 0){
            if(sem_post(&inChargeforAutomobile) != 0){
                perror("sem_post");
                return 1;
            }
            remainingAutomobileCars--;
        }
    }

    // Wait for the valet threads to finish
    if(pthread_join(valetForPickup, NULL) != 0 ||
        pthread_join(valetForAutomobile, NULL) != 0){
            perror("pthread_join failed");
            return 1;
    }

    // Destroy semaphores and mutex
    if(sem_destroy(&newPickup) != 0 ||
        sem_destroy(&newAutomobile) != 0 ||
        sem_destroy(&inChargeforPickup) != 0 ||
        sem_destroy(&inChargeforAutomobile) != 0 ||
        pthread_mutex_destroy(&newCar) != 0){
            perror("Destroy failed");
            return 1;
    }

    return 0;
}
