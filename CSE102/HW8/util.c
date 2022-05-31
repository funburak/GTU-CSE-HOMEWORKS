#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void generate_sequence(int xs, int currentlen, int seqlen, int *seq){
    int ce;
    if(currentlen>seqlen){
        return;
    }
    else{
        ce=xs;
        seq[0]=ce; // Everytime store the current element into the array's first index
        if(ce % 2==0){
            ce=ce/2;
            currentlen++;
            generate_sequence(ce,currentlen,seqlen,&seq[1]); // Each time the function is called I shift the array by 1
        }
        else if(ce % 2!=0){
            ce=3*ce+1;
            currentlen++;
            generate_sequence(ce,currentlen,seqlen,&seq[1]); // Each time the function is called I shift the array by 1 
        }
    }
} // end generating sequence

void check_loop_iterative(void (*f) (int,int,int,int *), int xs, int seqlen, int *loop, int *looplen){
    static int flag=0;
    int ls,le;
    int *seq=(int *)malloc(seqlen*(sizeof(int)));
    generate_sequence(xs,1,seqlen,seq);
    if(flag==0){ // Only printing the sequence once using flag
        printf("{");
        for(int i=0;i<seqlen;i++){
            printf("%d, ",seq[i]);
                if(i==seqlen-1){
                    printf("\b\b}"); // deleting the last comma sign
                }
        }
        printf("\n");   
        flag=1;
    }
    if(*looplen<2){
        *looplen=0;
        return;
    }
    else{
        printf("Checking if there is a loop of length %d...\n",*looplen);
            if(has_loop(seq,seqlen,*looplen,&ls,&le)==1){ // If the given sequence has a loop
                printf("Loop detected with a length of %d\n",*looplen);
                printf("The indexes of the loop's first occurance: %d (first digit), %d (last digit)\n",ls,le);
                for(int i=0;i<*looplen;i++){
                    loop[i]=seq[ls]; // Filling the loop 
                    ls++;
                }
                return;
            }
            else{
                (*looplen)--;
                check_loop_iterative(generate_sequence,xs,seqlen,loop,looplen);
            }
    }
} // end checking the loop iterative

int has_loop(int *arr, int n, int looplen, int *ls, int *le){
    int i,j;
    for(i=n-looplen-1;i>0;i--){
        for(j=n-1;j>n-looplen;j--){
            if(arr[i]!=arr[j]){
                return 0;
            }
            else if(arr[i]==arr[j]){ // If a loop has found 
                *ls=i-looplen+1;
                *le=i;
                return 1;
            }
        }
    }
} // end looking for a loop

void hist_of_firstdigits(void (*f) (int, int, int, int *), int xs, int seqlen, int *h, int digit){
    int *seq=(int *)malloc(seqlen*(sizeof(int)));
    generate_sequence(xs,1,seqlen,seq);
        if(digit==10){
            return;
        }
        else{
            for(int i=0;i<seqlen;i++){
                if(first_digit(seq[i])==digit){
                    h[digit-1]++; // Increment the digit index in array by 1 if the digit and the first digit of the number is equal
                }
            }
            digit++;
            hist_of_firstdigits(generate_sequence,xs,seqlen,h,digit);
        }
} // end histogram of the first digits

int first_digit(int n){
    if(n<10){
        return n;
    }
    else{
        return first_digit(n/10);
    }
} // end finding the first digit of a number