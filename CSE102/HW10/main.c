#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STACK_BLOCK_SIZE 10

typedef struct stack{
    int *array;
    int currentsize;
    int maxsize;
}stack;

void push(stack *s, int d);
int pop(stack *s);
stack *init_return();
int init(stack *s);
void print_movement(int s, int d, int disk);
void moveto(stack *s, stack *d, int A, int C);
void TowerOfHanoi(stack *s, stack *a, stack *d,int size);


int main(){
    int size,i;
    struct stack *A,*B,*C;
    A=init_return(); // First tower
    B=init_return(); // Second tower
    C=init_return(); // Third tower
    if(init(A) && init(B) && init(C)){
        printf("Enter tower size: ");
        scanf("%d",&size);
        for(i=size;i>=1;i--){ // Fill the first tower with integers starting from larger numbers
            push(A,i);
        }
        printf("First tower integer order: ");
        for(i=0;i<size;i++){ // Printing the first towers array
            printf("%d ",A->array[i]);
        }
        printf("\n");
        TowerOfHanoi(A,B,C,size);
    }
    return 0;
} // end main

// This functions adds integer d to the stack array
void push(stack *s, int d){
    if(s->currentsize > s->maxsize-1){ // If the STACK_BLOCK_SIZE is exceeded, reallocate the stack array size by increasing the maxsize 10
        s->maxsize+=10;
        s->array=(int *)realloc(s->array,s->maxsize);
    }
    else{
    s->array[s->currentsize]=d;
    s->currentsize++;
    }
} // end push

// This function returns the first integer in the stack
int pop(stack *s){
    if(s->currentsize==0){ // If the stack is empty
        return 0;
    }
    else{
        int pop_first=s->array[s->currentsize-1];
        s->currentsize--;
        return pop_first;
    }
} // end pop

// This function initialize the stacks and returns them
stack *init_return(){
    struct stack *temp;
    temp=(struct stack*)malloc(sizeof(stack));
    temp->array=(int *)malloc(STACK_BLOCK_SIZE*sizeof(int));
    temp->currentsize=0;
    temp->maxsize=STACK_BLOCK_SIZE;
    return temp;
} // end initializing an empty stack

// This function checks whether an empty stack is initiliazed
int init(stack *s){
    if(s->currentsize==0){
        return 1;
    }
    else{
        return 0;
    }
} // end checking initialization

// This functions prints the movement of disks from one stack to another
void print_movement(int s, int d, int disk){
    printf("Move the disk %d from '%d' to '%d'\n",disk,s,d);
} // end printing movement

// This function move disks from two towers by checking their first integer in the stack
void moveto(stack *s, stack *d,int A, int C){
    int sfirst,dfirst;
    sfirst=pop(s); // First integer in the stack 's'
    dfirst=pop(d); // First integer in the stack 'd'

    if(sfirst==0){ // When stack 's' is empty
        push(s,dfirst);
        print_movement(C,A,dfirst);
    }
    else if(dfirst==0){ // When stack 'd' is empty
        push(d,sfirst);
        print_movement(A,C,sfirst);
    }
    else if(sfirst > dfirst){ // When stack 's' first integer is higher than stack 'd' first integer
        push(s,sfirst);
        push(s,dfirst);
        print_movement(C,A,dfirst);
    }
    else if(sfirst < dfirst){ // When stack 'd' first integer is higher than stack 's' first integer
        push(d,dfirst);
        push(d,sfirst);
        print_movement(A,C,sfirst);
    }
} // end move to

// This functions first calculates the total move needed to implement tower of hanoi problem. Then checks for the first integer in the tower
void TowerOfHanoi(stack *s, stack *a, stack *d,int size){
    int A=1; // First tower
    int B=2; // Second tower
    int C=3; // Third tower
    int i=1;
    int total_move=pow(2,size)-1;
    while(i<=total_move){
        if(i%3==1){
            moveto(s,d,A,C);
        }
        else if(i%3==2){
            moveto(s,a,A,B);
        }
        else if(i%3==0){
            moveto(a,d,B,C);
        }
        i++;
    }
} // end implementing tower of hanoi
