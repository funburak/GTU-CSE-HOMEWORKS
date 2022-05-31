#include <stdio.h>
#include <math.h>

int sum(int n1, int n2, int flag);
int multi(int n1, int n2, int flag);
int isprime(int a);
void write_file(int number);
void print_file();
void sort_file();


int main(){
	int selection,choice,even_odd;
	int number1,number2;
	int result_0,result_1;
	int number;
	int prime;
	do{
	printf("Select operation (Enter '0' to quit)\n");
	printf("1. Calculate sum/multiplication between two numbers\n");
	printf("2. Calculate prime numbers\n");
	printf("3. Show number sequence in file\n");
	printf("4. Sort number sequence in file\n");
	printf("-------------------------------\n");
	scanf("%d",&selection);
	switch(selection){
	case 0:
		printf("Exiting...\n");
		break;
	
	case 1:
		printf("Please select '0' for sum, '1' for multiplication.\n");
		scanf("%d",&choice);
		if((choice==1) || (choice==0)){
		
			if(choice==0){ /* Summation */
			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
			scanf("%d",&even_odd);
			printf("Please enter two different numbers\n");
			printf("Number 1: ");
			scanf("%d",&number1);
			printf("Number 2: ");
			scanf("%d",&number2);
			if(number1==number2){
				printf("Please enter two different numbers\n");
				printf("Number 1: ");
				scanf("%d",&number1);
				printf("Number 2: ");
				scanf("%d",&number2);
			}
			else if((number1-number2==1) || (number2-number1==1)){ /* If the numbers are consecutive */
				printf("Enter two numbers which their difference is greater than 1\n");
				printf("Number 1: ");
				scanf("%d",&number1);
				printf("Number 2: ");
				scanf("%d",&number2);
			}
			printf("Result\n");
			result_0=sum(number1,number2,even_odd);
			write_file(result_0);
			printf("The result is written to the results.txt file.\n");
			}
			
			else if(choice==1){ /* Multiplication */
			printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
			scanf("%d",&even_odd);
			printf("Number 1: ");
			scanf("%d",&number1);
			printf("Number 2: ");
			scanf("%d",&number2);
			if(number1==number2){
				printf("Please enter two different numbers\n");
				printf("Number 1: ");
				scanf("%d",&number1);
				printf("Number 2: ");
				scanf("%d",&number2);
			}
			else if((number1-number2==1) || (number2-number1==1)){ /* If the numbers are consecutive */
				printf("Enter two numbers which their difference is greater than 1\n");
				printf("Number 1: ");
				scanf("%d",&number1);
				printf("Number 2: ");
				scanf("%d",&number2);
			}
			printf("Result\n");
			result_1=multi(number1,number2,even_odd);
			write_file(result_1);
			printf("The result is written to the results.txt file.\n");
			}
			}
			else{
				printf("Error. Type '0' or '1'");
			}
			break;
				
	case 2:
		printf("Please enter an integer: ");
		scanf("%d",&number);
		if(number<=2){
			printf("Enter an integer that is greater than 2: ");
			scanf("%d", &number);
		}
		for(int j=2;j<number;j++){
		prime=isprime(j);
		if(prime==j){
			printf("%d is a prime number.\n",prime);
		}
		}
		break;
	
	case 3:
		printf("Result:\n");
		print_file();
		break;
	
	case 4:
		printf("Sorting is complete.\n");
		printf("Result: \n");
		sort_file();
		break;
		
	default:
		printf("Error. Type valid number from the menu\n");
		break;
	}
	
	}while(selection!=0); /*enter '0' to exit  from the menu */
	
	return 0;
}



int sum(int n1, int n2, int flag){
	int result=0;
	int temp;
	if(n1>n2){  /* If n1 is greater than n2, I swap them */
		temp=n1;
		n1=n2;
		n2=temp;
		if(flag==0){   /* to work on even numbers */
		for(int i=n1+1;i<n2;i++){
			if(i%2==0){
				result+=i;
			printf("%d + ",i);
			}
			if(i==n2-1){
					printf("\b\b"); /* deleting the last '+' sign before '=' sign */
				}
			
		}
		printf("= %d\n",result);	
	}
	
	else if(flag==1){   /* to work on odd numbers */
		for(int i=n1+1;i<n2;i++){
			if(i%2!=0){
				result+=i;
				printf("%d + ",i);
				}
				if(i==n2-1){
					printf("\b\b"); /* deleting the last '+' sign before '=' sign */
				}
			
		}
		printf("= %d\n",result);
	
	}
	}
	else{
	if(flag==0){   /* to work on even numbers */
		for(int i=n1+1;i<n2;i++){
			if(i%2==0){
				result+=i;
			printf("%d + ",i);
			}
			if(i==n2-1){
				printf("\b\b"); /* deleting the last '+' sign before '=' sign */
			}
		}
		printf("= %d\n",result);
	}
	else if(flag==1){   /* to work on odd numbers */
		for(int i=n1+1;i<n2;i++){
			if(i%2!=0){
				result+=i;
				printf("%d + ",i);
			}
			if(i==n2-1){
				printf("\b\b"); /* deleting the last '+' sign before '=' sign */
				}
		}
		printf("= %d\n",result);
	}
	}
	return result;	
}    /* end sum */

int multi(int n1, int n2, int flag){
	int result=1;
	int temp;
	if(n1>n2){  /* If n1 is greater than n2 I swap them */
		temp=n1;
		n1=n2;
		n2=temp;
		if(flag==0){   /* to work on even numbers */
			if((n1%2==0) && (n2%2==0)){ /* If the numbers are consecutive even numbers */
				if(n2-n1==2){
					result=0;
				}
			}
		for(int i=n1+1;i<n2;i++){
			if(i%2==0){
				result*=i;
			printf("%d * ",i);
			}
			if(i==n2-1){
					printf("\b\b"); /* deleting the last '*' sign before '=' sign */
				}
		}
		printf("= %d\n",result);
	}
	else if(flag==1){   /* to work on odd numbers */
		if((n1%2!=0) && (n2%2!=0)){ /* If the numbers are consecutive odd numbers */
			if(n2-n1==2){
				result=0;
			}
		}
		for(int i=n1+1;i<n2;i++){
			if(i%2!=0){
				result*=i;
				printf("%d * ",i);
			}
			if(i==n2-1){
					printf("\b\b"); /* deleting the last '*' sign before '=' sign */
				}
		}
		printf("= %d\n",result);
	}
	}
	else{
	if(flag==0){   /* to work on even numbers */
		if((n1%2==0) && (n2%2==0)){ /* If the numbers are consecutive even numbers */
				if(n2-n1==2){
					result=0;
				}
			}
		for(int i=n1+1;i<n2;i++){
			if(i%2==0){
				result*=i;
				printf("%d * ",i);
			}
			if(i==n2-1){
					printf("\b\b"); /* deleting the last '*' sign before '=' sign */
				}
		}
		printf("= %d\n",result);
	}
	else if(flag==1){   /* to work on odd numbers */
		if((n1%2!=0) && (n2%2!=0)){ /* If the numbers are consecutive odd numbers */
			if(n2-n1==2){
				result=0;
			}
		}
		for(int i=n1+1;i<n2;i++){
			if(i%2!=0){
				result*=i;
				printf("%d * ",i);
			}
			if(i==n2-1){
					printf("\b\b"); /* deleting the last '*' sign before '=' sign */
				}
		}
		printf("= %d\n",result);
	}
	}
	return result;
	
}    /* end multiplication */

int isprime(int a){
	for(int i=2;i<=sqrt(a);i++){
		if(a%i==0){
		printf("%d is not a prime number, it is dividible by %d.\n",a,i); 
			return i; /* returning the first divisor */
			}
			
		}
	return a; /* returning the input if it is a prime number */
} /* end prime check */

void write_file(int number){
	FILE *write;
	write=fopen("results.txt","a");
	fprintf(write,"%d ",number);
	fclose(write);
} /* end file writing */


void print_file(){
	int numbers;
	FILE *print;
	print=fopen("results.txt","r");
	if(print==NULL){
		printf("There isn't a results.txt file\n");
	}
	while(!feof(print)){
		if(feof(print)==1)
			break;
		fscanf(print,"%d ",&numbers);
		printf("%d ",numbers);
	}
	printf("\n");
	fclose(print);
} /* end printing the file */

void sort_file(){ /* It works only there are 3,4 and 5 numbers in the file */
	int numbers;
	int count=0;
	int min1,min2,min3;
	int temps1,temps2,temps3;
	FILE *sort;
	FILE *temp;
	sort=fopen("results.txt","r");
	temp=fopen("temporary.txt","a");
	if(sort==NULL){
		printf("Cannot open file\n");
	}
	while(!feof(sort)){
		if(feof(sort)==1) break;
		fscanf(sort,"%d ",&numbers);
			count++;
			if(count==1){ 
				min1=numbers;
				}
			else if(count==2){
			if(numbers<min1){
				min2=min1;
				min1=numbers;
				}
			else{
				min2=numbers;
			}
				}
			else if(count==3){
			if((numbers<min1) && (numbers<min2)){
				min3=min2;
				min2=min1;
				min1=numbers;
			}
			else if((numbers>min1) && (numbers>min2)){
				min3=numbers;
			}
			else if((numbers>min1) && (numbers<min2)){
				min3=min2;
				min2=numbers;
			}
			printf("%d %d %d\n",min1,min2,min3);
			}
			
			else if(count==4){
				if(numbers<min1){
					temps1=min3;
					min3=min2;
					min2=min1;
					min1=numbers;					
				}
				else if((numbers>min1) && (numbers<min2)){
					temps1=min3;
					min3=min2;
					min2=numbers;
				}
				else if((numbers>min2) && (numbers<min3)){
					temps1=min3;
					min3=numbers;
				}
				else{
					temps1=numbers;
				}
				printf("%d %d %d %d\n",min1,min2,min3,temps1);
			}
			else if(count==5){
				if(numbers>temps1){
					temps2=numbers;
				}
				if(numbers<min1){
					temps2=min3;
					min3=min2;
					min2=min1;
					min1=numbers;					
				}
				else if((numbers>min1) && (numbers<min2)){
					temps2=min3;
					min3=min2;
					min2=numbers;
				}
				else if((numbers>min2) && (numbers<min3)){
					temps2=min3;
					min3=numbers;
				}
				printf("%d %d %d %d %d\n",min1,min2,min3,temps1,temps2);
			}
		}
	fclose(sort);
	sort=fopen("results.txt","a");
	fprintf(temp,"%d %d %d ",min1,min2,min3);
	fprintf(sort,"%d %d %d ",min1,min2,min3);
	fclose(temp);
	fclose(sort);		
} /* end sorting the file */


