#include <stdio.h>
#define x_max 55
#define y_max 15

void graph(int a, int b, int c);
void graph_txt(int a, int b, int c);

int main(){
    int operation;
    int a,b,c;
    FILE *coef;
    do{
        printf("Selet operation\n");
        printf("1. Enter the coeeficients.\n");
        printf("2. Draw the graph.\n");
        printf("3. Print the graph into a .txt file.\n");
        printf("4. Exit");
        printf("\n");
        scanf("%d",&operation);
        
        switch(operation){
            case 1:
            printf("Please enter the coefficients for the following equation: x=a*(y*y)+b*y+c\n");
            printf("a: ");
            scanf("%d",&a);
            printf("b: ");
            scanf("%d",&b);
            printf("c: ");
            scanf("%d",&c);
            coef=fopen("coefficients.txt","w");
            fprintf(coef,"%d\n%d\n%d",a,b,c);
            fclose(coef);
            break;

            case 2:
            coef=fopen("coefficients.txt","r");
            fscanf(coef,"%d\n%d\n%d",&a,&b,&c);
            printf("Coefficients has been read from the coefficients.txt file\n");
            graph(a,b,c);
            break;

            case 3:
            coef=fopen("coefficients.txt","r");
            if(coef==NULL) printf("Error. Cannot find coefficients.txt file\n");
            fscanf(coef,"%d\n%d\n%d",&a,&b,&c);
            printf("Coefficients has been read from the coefficients.txt file\n");
            graph_txt(a,b,c);
            printf("The graph of x=%d*(y*y)+%d*y+%d has been written to the graph.txt file\n",a,b,c);
            break;

            case 4:
            printf("Exiting...\n");
            break;

            default:
            printf("Enter valid operation from the menu\n");
        }
    }while(operation!=4);
    return 0;
} /* end main */

void graph(int a, int b, int c){
    int x,y;
    for(int a=0;a<56;a++){
        printf(" ");
    }
    printf("^");
    printf("\n");
    for(y=y_max;y>=-y_max;y--){
        for(x=-x_max-1;x<=x_max+1;x++){
            if(x==a*(y*y)+b*y+c){   /* for the polynomail graph */
                printf("\033[0;34m");   /* set color to blue */
                printf("#");
                printf("\033[0m");  /* set color to default */
            }
            else{
            if(x==0){   /* y-axis */
                printf("|");
            }
            else if((x==56) && (y==0)){
                printf(">");
            }
            else if((x==-56) && (y==0)){
                printf("<");
            }
            else if((y==0) && (x!=0)){  /* x-axis */
                printf("-");
            }
            else{
                printf(" ");
            }
            if(x==-2){  /* display the y coordinates */
                if((y%5==0) && (y!=0)){
                    if(y==5){
                    printf("\b"); /* delete 1 char beacuse 5 has 1 digit */
                }
                else if(y==-5){
                    printf("\b\b"); /* delete 2 chas beacuse of the '-' sign */
                }
                else if(y==10){
                    printf("\b\b"); /* delete 2 characters beacuse 10 has 2 digits */
                }
                else if(y==15){
                    printf("\b\b"); /* delete 2 characters beacuse 15 has 2 digits */
                }
                else if(y<-5){
                    printf("\b\b\b"); /* delete 3 characters beacuse of the '-' sign and the numbers have two digits */
                }
                    printf("\033[0;33m"); /* set color to yellow */
                    printf("%d",y);
                    printf("\033[0m"); /* set color to default */
                }
            }
            if(y==-1){ /* display the x coordinates */
                if(x%10==0){
                    if(x<0){
                        printf("\b\b\b"); /* delete three characters because of the '-' sign and the numbers have two digits  */
                    }
                    else if(x==0){ 
                        printf("\b");   /* delete one character beacuse 0 has 1 digits */
                    }
                    else if(x>0){
                        printf("\b\b");  /* If x is greater than 0, I delete two characters because the displayed numbers are two digits */
                    }
                    printf("\033[0;33m");   /* set color to yellow */
                    printf("%d",x);
                    printf("\033[0m");   /* set color to default */
                }
            }
        }
        }
        printf("\n");
    }
} /* end graph */

void graph_txt(int a, int b, int c){
    int x,y;
    FILE *graph;
    graph=fopen("graph.txt","w");
    for(int a=0;a<56;a++){
        fprintf(graph," ");
    }
    fprintf(graph,"^");
    fprintf(graph,"\n");
    for(y=y_max;y>=-y_max;y--){
        for(x=-x_max-1;x<=x_max+1;x++){
            if(x==a*(y*y)+b*y+c){
                fprintf(graph,"#");
            }
            else{
            if(x==0){ /* y-axis */
                fprintf(graph,"|"); 
            }
            else if((x==56) && (y==0)){
                fprintf(graph,">");
            }
            else if((x==-56) && (y==0)){
                fprintf(graph,"<");
            }
            else if((y==0) && (x!=0)){ /* x-axis */
                fprintf(graph,"-");
            }
            else{
                fprintf(graph," ");
            }
        }
        }
        fprintf(graph,"\n");
    }
    fclose(graph);
} /* end graph txt file */
