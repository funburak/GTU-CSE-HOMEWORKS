#include <stdio.h>
#include <string.h> /* For the strlen function */
#include "utils.h"

int find_divisible(int x, int y ,int z){
	int divisors[10];
	int n;
	int f_i;
	int j=0;
	if(x<y){
	for(int i=x+1;i<y;i++){
		if(i%z==0){	
		divisors[j]=i; 	/* storing the divisors in an array */
		j++;		
		printf("The first integer between %d and %d that is divided by %d is %d\n",x,y,z,divisors[0]);
		return divisors[0];	/* returning the first integer */
		}
		if(i==y-1){
		printf("There is not any integer between %d and %d that is divided by %d\n",x,y,z);			
		}
		}
	}else{
		printf("There is not any integer between %d and %d that is divided by %d\n",x,y,z);
	}
	
}	/* end find divisible */	
	

int find_nth_divisible(int n ,int f_i,int z){
	int nth_divisor;
	nth_divisor=f_i+n*z;
	return nth_divisor;

}/*end find nth divisible */
	
int validate_identity_number(char identity_number[]){
	int sum1=(identity_number[0]+identity_number[2]+identity_number[4]+identity_number[6]+identity_number[8])-48*5; /* sum of the first, third, fifth, seventh and ninth digits */
	int sum2=(identity_number[1]+identity_number[3]+identity_number[5]+identity_number[7])-48*4; /* sum of the second, fourth, sixth and eight digits */
	int diff=(sum1*7)-sum2; 
	if(strlen(identity_number)==11){ 	/* If the id number is 11 digit long */
		
		if(identity_number[0]=='0'){ 	/* If the first digit of the id number is 0 */
			return 0;
	}
	if((diff%10==identity_number[9]-48) && (sum1+sum2+identity_number[9]-48)%10==identity_number[10]-48){
		return 1;
	}
	else{
		return 0;
	}	
	
		for(int i=0;i<strlen(identity_number);i++){
			if((identity_number[i]>='0') && (identity_number[i]<='9')){ /* If the id number's digits are a digit */
				return 1;
			}
			else{
				return 0;
			}
		}
	
}
else{
	return 0;
}
} /* end of validate identity number check */

int create_customer(char identity_number[], int password){
		FILE *customer_info;
		customer_info=fopen("customeraccount.txt","w");
		if(customer_info==NULL){ /* If the file cannot be opened */
			printf("Error, cannot open file");
			fclose(customer_info);
}
		else{
			fprintf(customer_info,"%s,%d",identity_number,password);
			fclose(customer_info);
		} 
} 	/* end of creating customer info txt */
int check_login(char identity_number[], int password){
	char identity_number_check[30];
	char password_check[10];
	char identity_no_check[30];
	char password_login[10];
	int check_id,check_pass;
		printf("Enter your identity number: ");
		scanf("%s",identity_no_check);
		if(strlen(identity_no_check)!=11){ 	/* If the login id is not 11 digits */
		printf("Id number must be 11 digit. Please try again: "); 
		scanf("%s",identity_no_check);
		}
		printf("Enter your password: ");
		scanf("%s",password_check);
		FILE *customer_info;
		customer_info=fopen("customeraccount.txt","r");
		fscanf(customer_info,"%[^,],%s",identity_number_check,password_login); /* [^,] sign scans the array until comma */
	fclose(customer_info);
		for(int i=0;i<11;i++){
			if((identity_number_check[i]==identity_no_check[i])){
				check_id=1;
			}
			else{
				check_id=-1;
			}
			}	
			for(int j=0;j<4;j++){
				if(password_login[j]==password_check[j]){
					check_pass=1;
				}
				else{
					check_pass=-1;
		}
			
		}
		if(check_id==1 && check_pass==1){
			return 1;
		}
		else if(check_id==-1 || check_pass==-1){
			return 0;
		}
		
		
	
}	/* end of checking the login attempt */


int withdrawable_amount(float cash_amount){
	int money;
	money=(int)cash_amount; /* changing float into integer */
	printf("Wtihdrawable amount is %d\n",money-(money%10));	
	
} /* end of withdraw amount check */

