#include <stdio.h>
#include "utils.h"

int main(){
	int x,y,z,f_i,n,nth_divisor,valid_identity,password;
	char identity_no[100];
	int login_check;
	float money;
	int withdraw_check;
	printf("Enter the first integer: ");
	scanf("%d",&x);
	printf("Enter the second integer: ");
	scanf("%d",&y);
	printf("Enter the divisor: ");
	scanf("%d",&z);
	f_i=find_divisible(x,y,z);
	if(f_i>x && f_i<y){ 	/* If the first integer is between x and y */
	printf("Enter the number how many next: ");
	scanf("%d",&n);
	}
	nth_divisor=find_nth_divisible(n,f_i,z);
	if(nth_divisor>=y){ 	/* If nth divisible if out of range */
		printf("No possible to find %dth divisible between %d and %d divided by %d\n",n+1,x,y,z);
	}
	else{
		printf("The %d. integer between %d and %d divided by %d is %d\n",n+1,x,y,z,nth_divisor);
	}	
	printf("Enter identity number: ");
	scanf("%s",identity_no);
	valid_identity=validate_identity_number(identity_no);
	if(valid_identity==1){ 	/* If the identity is valid */
		printf("Valid identity number\n");
		printf("Enter your password: ");
		scanf("%d",&password);
		password=create_customer(identity_no,password);
		login_check=check_login(identity_no,password);
		if(login_check==1){ 	/* If login is successful */
			printf("Login Successful\n");
				printf("Enter your withdraw amount: ");
				scanf("%f",&money);
				withdraw_check=withdrawable_amount(money);
		}
		
		else if(login_check==0){
			printf("Invalid identity number or password\n");
		}
		
		
	}
	else if(valid_identity==0){
		printf("Invalid identity number\n");
	}
	
return 0;

}
