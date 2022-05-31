#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int main(){
    int length,i;
    int first;
    int looplen;
    int *loop,*histogram;
    printf("Please enter the sequence length: ");
    scanf("%d",&length);
    printf("Please enter the first element: ");
    scanf("%d",&first);
    printf("Sequence: ");
    looplen=length/2;
    loop=(int *)malloc(looplen*sizeof(int)); // Allocate looplen size of memory byte for loop array
    check_loop_iterative(generate_sequence,first,length,loop,&looplen);
    if(looplen!=0){ // If a loop has found in the sequence
    printf("Loop: {");
        for(i=0;i<looplen;i++){
            printf("%d, ",loop[i]);
                if(i==looplen-1){
                    printf("\b\b}\n"); // Deleting the last comma sign
                }
        }
    }
    if(looplen==0){
        printf("No loop found\n");
    }
    histogram=(int *)calloc(9,sizeof(int)); // Allocate 9 memory byte space for histogram array
    hist_of_firstdigits(generate_sequence,first,length,histogram,1);
    printf("Histogram of the sequence :{");
    for(i=0;i<9;i++){
        printf("%d, ",histogram[i]);
            if(i==8){
                printf("\b\b}\n"); // Deleting the last comma sign
            }
    }
    return 0;
} // end main
