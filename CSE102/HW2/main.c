#include <stdio.h>
#include <stdlib.h>
#include "util.h"


int main() {
	double PL,PW,SL,SW,x1,x2,x3;
	int x4,x5;
	int selection;
	double agno,grade;
	int semester,year,month;
	int problem;
	char data1a,data1b;
	double data2a,data2b;
	char data3a,data3b;
	
	do{
	printf("Enter the problem you want to solve (Enter 0 to exit): ");
	scanf("%d",&selection);
	
	switch(selection){
	
	case 0: /* Exit case */
		printf("Exiting...\n");
		break;
		
	case 1: /* Data1a and data1b */
		printf("Enter real numbers for PL, PW, SL and SW\n");
		scanf("%lf %lf %lf %lf",&PL,&PW,&SL,&SW); /* SL and SW are not in the used in the decision nodes but I send that values to the functions */
		data1a=dt1a(PL,PW,SL,SW); 
		data1b=dt1b(PL,PW,SL,SW);
		if(data1a=='S'){
			if(data1b=='S'){
				printf("Answer is Setosa\n");
			}
			else if(data1b=='c'){
				printf("Answer of data a is Setosa\n");
				printf("Answer of data b is Versicolor\n");
			}
			else if(data1b=='V'){
				printf("Answer of data a is Setosa\n");
				printf("Answer of data b is Virginica\n");
			}
		}
		else if(data1a=='c'){
			if(data1b=='S'){
				printf("Answer of data a is Versicolor\n");
				printf("Answer of data b is Setosa\n");
			}
			else if(data1b=='c'){
				printf("Answer is Versicolor\n");
			}
			else if(data1b=='V'){
				printf("Answer of data a is Versicolor\n");
				printf("Answer of data b is Virginica\n");
			}
		}
		else if(data1a=='V'){
			if(data1b=='S'){
				printf("Answer of data a is Virginica\n");
				printf("Answer of data b is Setosa\n");
			}
			else if(data1b=='c'){
				printf("Answer of data a is Virginica\n");
				printf("Answer of data b is Versicolor\n");
			}
			else if(data1b=='V'){
				printf("Answer is Virginica\n");
			}
		}		
		break;
	case 2: /* Data2a and data2b */
		printf("Enter real numbers for x1, x2 and x3\n");
		scanf("%lf %lf %lf",&x1,&x2,&x3);
		printf("Enter binary value '0' or '1' for x4: ");
		scanf("%d",&x4);
		printf("Enter binary value '0' or '1' for x5: ");
		scanf("%d",&x5);
		data2a=dt2a(x1,x2,x3,x4,x5);
		data2b=dt2b(x1,x2,x3,x4,x5);
		if((data2a-data2b==CLOSE_ENOUGH) ||(data2b-data2a==CLOSE_ENOUGH)){ 
			printf("Answer is %lf\n",(data2a+data2b)/2);
		}
		else{
		printf("Answer of data a is %.3lf\n",data2a);
		printf("Answer of data b is %.3lf\n",data2b);
		}
		break;
		
	case 3: /* Data3a and data3b */
		printf("Enter your agno: ");
		scanf("%lf",&agno);
		if((agno<0.00) || (agno>4.00)){
			printf("Try again. Agno must be between 0 and 4.00 (including 0 and 4.00): ");
			scanf("%lf",&agno);
		}
		printf("Enter your Erasmus exam grade: ");
		scanf("%lf",&grade);
		if((grade<0.0) || (grade>100.0)){
			printf("Try again. Grade must be between 0 and 100 (including 0 and 100): ");
			scanf("%lf",&grade);
		}
		printf("Enter your semester '0' for fall, '1' for spring: ");
		scanf("%d",&semester);
		printf("Enter your year at the university (excluding preparation year): ");
		scanf("%d",&year);
		if((year<=0) && (year>4)){
			printf("Try again. Year must be between 1 and 4 (including 1 and 4): ");
			scanf("%d",&year);
		}
		printf("Enter which month you want to go with numbers 1 to 12: ");
		scanf("%d",&month);
		if((month<=0) || (month>12)){
			printf("Try again. There are 12 months: ");
			scanf("%d",&month);
		} 
		do{
		printf("Choose your decision, '0' for Eramus apply and '1' for Erasmus donation (enter '2' to exit): ");
		scanf("%d",&problem);
		if(problem==0){
		data3a=dt3a(agno,grade,year,semester,month);
		if(data3a==1){
			printf("Congrats have a nice Erasmus journey.\n");
		}
		else if(data3a==0){
			printf("Sorry, you cannot have an Erasmus journey.\n");
		}
		else if(data3a==2){
			printf("Try again next year.\n");
		}
		}
		else if(problem==1){
		data3b=dt3b(agno,grade,year,semester,month);
		if(data3b==1){
			printf("Congrats you will be donated 500€ per month till the end of your Erasmus journey.\n");
		}
		else if(data3b==0){
			printf("Sorry, you are not going to be donated in your Erasmus journey.\n");
		}
		else if(data3b==2){
			printf("Congrats you will be donated 250€ per month till the end of your Erasmus jorney.\n");
		}
		else if(data3b==3){
			printf("Congrats you will be donated 150€ per month till the end of your Erasmus jorney.\n");
		}
		}	
		}while(problem!=2);
		break;
	default:
		printf("There is not problem %d\n",selection);
	} 	/* end of switch-case */
	}while(selection!=0);
		

    /* Ask for the problem selection (1,2,3) .....  */

    /* Get the input from the user for the first problem, i.e., to test dt1a and dt1b */
    /* Compare performances and print results */

    /* Get the input from the user for the second problem, i.e., to test dt2a and dt2b */
    /* Compare performances and print results */

    /* Get the input from the user for the third problem, i.e., to test dt3a and dt3b */
    /* Compare performances and print results */

    return 0;
}
