#include <stdio.h>

union Person{
    char name[50];
    char address[50];
    int phone;
};

union Loan{
    float array[3]; // [0] amount, [1] period, [2] interest rate 
};

struct BankAccount{
    union Person Customer;
    union Loan Loans[3];
};

void listCustomers();
void addCustomer(struct BankAccount customers[], int i);
void newLoan(struct BankAccount customers[]);
double calculateLoan(float amount, int period, float interestRate);
void getReport(struct BankAccount customers[]);

int id=1;
int loancounter[50]={0};

int main(){
    struct BankAccount customers[50];
    int selection,i=0;

    do{
        printf("=====================================\n");
        printf("Welcome to the Bank Management System\n");
        printf("=====================================\n");
        printf("1. List all customers\n");
        printf("2. Add New Customer\n");
        printf("3. New Loan Application\n");
        printf("4. Report Menu\n");
        printf("5. Exit System\n");
        scanf("%d",&selection);

            switch(selection){
                case 1:
                    listCustomers();
                    break;
                case 2:
                    addCustomer(customers,i);
                    i++;
                    break;
                case 3:
                    newLoan(customers);
                    break;
                case 4:
                    getReport(customers);
                    break;
                case 5:
                    printf("Exiting...\n");
                    break;
            }

    }while(selection!=5);

    return 0;
} // end main

// This function prints the names of the customers from the txt
void listCustomers(){
    int ID,phone;
    char name[50][20],address[50];
    FILE *customer;
    customer=fopen("customers.txt","r");
    if(customer==NULL){
        printf("There is not such a file\n");
        return;
    }
    for(int i=0;i<id-1;i++){
        fscanf(customer,"%d %[^\n]%*c %d %s",&ID,name[i],&phone,address);
        printf("Customer Name = %s\n",name[i]);
    }
    fclose(customer);
} // end listing customer's name

// This function adds new customer to the system
void addCustomer(struct BankAccount customers[], int i){
    FILE *customer;
    customer=fopen("customers.txt","a+");
    fprintf(customer,"%d\n",id);
    id++;
    printf("Customer Name = ");
    getchar();
    scanf("%[^\n]%*c",(customers+i)->Customer.name);
    fprintf(customer,"%s\n",(customers+i)->Customer.name);
    printf("Customer Phone = ");
    scanf("%d",&(customers+i)->Customer.phone);
    fprintf(customer,"%d\n",(customers+i)->Customer.phone);
    printf("Customer Address = ");
    getchar();
    scanf("%[^\n]%*c",(customers+i)->Customer.address);
    fprintf(customer,"%s\n\n",(customers+i)->Customer.address);
    fclose(customer);
} // end adding new customer


// This function is for applying for a new loan
void newLoan(struct BankAccount customers[]){
    int ID;
    int i=0;
    double totalloan;
    FILE *loan;
    loan=fopen("loan.txt","a+");
    printf("Enter the id in range of [1-50] for the loan-needer : ");
    scanf("%d",&ID);
    if(loancounter[ID-1]<3){ // If the customer has applied less than 3 loans
        if(id>ID){ // If the given id is in the txt file
            fprintf(loan,"%d\n",ID);
            printf("Enter the amount: ");
            scanf("%f",&(customers+ID-1)->Loans[i].array[0]);
            fprintf(loan,"%f\n",(customers+ID-1)->Loans[i].array[0]);
            printf("Enter the period: ");
            scanf("%f",&(customers+ID-1)->Loans[i].array[1]);
            fprintf(loan,"%f\n",(customers+ID-1)->Loans[i].array[1]);
            printf("Enter the interest rate: ");
            scanf("%f",&(customers+ID-1)->Loans[i].array[2]);
            fprintf(loan,"%f\n",(customers+ID-1)->Loans[i].array[2]);
            totalloan=calculateLoan((customers+ID-1)->Loans[i].array[0],(int)(customers+ID-1)->Loans[i].array[1],(customers+ID-1)->Loans[i].array[2]);
            fprintf(loan,"%lf\n",totalloan);
            printf("Total Credit Value = %lf\n",totalloan);
            for(int j=0;j<(customers+ID-1)->Loans[i].array[1];j++){
                printf("%d. Month Installment = %.4f\n",j+1,totalloan/(customers+ID-1)->Loans[i].array[1]);
            }
            loancounter[ID-1]++;
            i++;
        }
        else{
            printf("Cannot find the customer with the ID %d\n",ID);
        }
    }
    else{
        printf("You cannot apply more than 3 loans\n");
    }
    fclose(loan);
} // end application for new loan

// This function calculates the loan with recursion
double calculateLoan(float amount, int period, float interestRate){
    if(period==0){
        return amount;
    }
    else{
        return (1+interestRate)*calculateLoan(amount,period-1,interestRate);
    }
} // end calculate loan

// This function prints the customers loan report

void getReport(struct BankAccount customers[]){
    int id[50],i=0,identity;
    double amount,period,interest,total[50]={0};
    FILE *loan;
    loan=fopen("loan.txt","r");
    if(loan!=NULL){
    while(!feof(loan)){
        fscanf(loan,"%d %lf %lf %lf %lf",id,&amount,&period,&interest,total);
        i++;
    }
    printf("Enter the id you want to get report: ");
    scanf("%d",&identity);
    for(i=0;i<50;i++){
        if(identity==id[i]){
            printf("Total month Installment= %lf\n",total[i]);
            for(int j=0;j<period;j++){
                printf("%d. Monnth Installment = %lf\n",j+1,total[i]/period);
            }
        }
    }
    }
    else{
        printf("File cannot found\n");
    }
    fclose(loan);    
} // end get report
