#ifndef __YACC_HELPER_H__
#define __YACC_HELPER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE *yyin; // for printing to file
void defineFunction(char *id, char *expression);
void defineFunctionWithParameters(char* id,char* explist,char* parameter1, char* parameter2);
void callFunctionOneParameter(char* id, char* parameter);
void callFunctionTwoParameter(char* id, char* parameter1, char* parameter2);

int gcd(int a, int b);
char* add(const char* a, const char* b);
char* subtract(const char* a, const char* b);
char* multiply(const char* a, const char* b);
char* divide(const char* a, const char* b);
char* concatenate(const char* operator, const char* exp1, const char* exp2);

int yylex(); 
int yyerror(const char *error){
    printf("Syntax Error!\n");
}

typedef struct Identifier{
    char idName[100][100];
    char valuefs[100][100];
}Identifier;

typedef struct IdentifierStruct{
    Identifier *ids;
    int size;
}IdentifierStruct;

typedef struct ParameterStruct{
    char parameterName[100][100];
    char *valuefs[100];
    int size;
}ParameterStruct;

typedef struct Function{
    char id[100][100];
    char explist[1][100];
    ParameterStruct* parameters;
}Function;

typedef struct FunctionStruct{
    int size;
    Function* funcs;
}FunctionStruct;

IdentifierStruct identifiers;
FunctionStruct functions;
ParameterStruct parameters;

void defineFunction(char *id, char *expression){
    for(int i=0;i< functions.size;i++){
        if(strcmp(functions.funcs[i].id,id)==0){
            printf("Error! %s already defined!\n",id);
            exit(-1);
        }
    }

    if(identifiers.size == 0 || identifiers.ids == NULL){
        identifiers.ids = (Identifier*) malloc(1);
        strcpy(identifiers.ids[0].idName,id);
        functions.size = 1;
    }
    else{
        identifiers.ids = (Identifier*) realloc(identifiers.ids,sizeof(Identifier) * (identifiers.size +1));
        strcpy(functions.funcs[functions.size].id,id);
        functions.size++;
    }

    if(functions.size==0 || functions.funcs==NULL){
        functions.funcs=(Function*) malloc(1);
        strcpy(functions.funcs[0].id,id);
        strcpy(functions.funcs[0].explist,expression);
        functions.size=1;
    }else{
        functions.funcs=(Function*) realloc(functions.funcs,sizeof(Function)*(functions.size+1));
        strcpy(functions.funcs[functions.size].id,id);
        strcpy(functions.funcs[functions.size].explist,expression);
        functions.size++;
    }
}

void defineFunctionWithParameters(char* id,char* explist,char* parameter1, char* parameter2){
    for(int i=0;i< functions.size;i++){
        if(strcmp(functions.funcs[i].id,id)==0){
            printf("Error! %s already defined!\n",id);
            exit(-1);
        }
    }
    
    if(functions.size == 0){
        functions.funcs = (Function*) malloc(sizeof(Function));
        printf("function created\n");
    }else{
        printf("new function\n");
        functions.funcs = (Function*) realloc(functions.funcs, sizeof(Function)* (functions.size +1));
    }

    if(functions.funcs == NULL){
        printf("Memory allocation failed\n");
        exit(-1);
    }

    strcpy(functions.funcs[functions.size].id,id);
    if (explist != NULL) {
        strcpy(functions.funcs[functions.size].explist, explist);
    }else{
        printf("Invalid explist\n");
        exit(-1);
    }

    functions.funcs[functions.size].parameters = (ParameterStruct*) malloc(sizeof(ParameterStruct));
    if (functions.funcs[functions.size].parameters == NULL) {
        printf("Memory allocation for parameters failed.\n");
        exit(-1);
    }

    functions.funcs[functions.size].parameters->size = (parameter2 != NULL) ? 2 : (parameter1 != NULL) ? 1 : 0;
    if (parameter1 != NULL) {
        strcpy(functions.funcs[functions.size].parameters->parameterName[0], parameter1);
    }
    if (parameter2 != NULL) {
        strcpy(functions.funcs[functions.size].parameters->parameterName[1], parameter2);
    }

    functions.size++;
}

void callFunctionOneParameter(char* id, char* parameter){
    int found = 0;
    int i=0;
    for(i=0;i< functions.size;i++){
        if(strcmp(functions.funcs[i].id,id)==0){
            found = 1;
            break;
        }
    }

    if(found){
        strcpy(functions.funcs[i].parameters->valuefs,parameter);
        char operator = functions.funcs[i].explist[0][0];
        char *expression = strdup(functions.funcs[i].explist[0]);
        char *token = strtok(expression," ");
        char *operand;
        while(token != NULL){
            if(strstr(token,"b")!= NULL){
                operand = strdup(token);
                break;
            }
            token = strtok(NULL," ");
        }
        switch (operator){
        case '+':
            add(functions.funcs[i].parameters->valuefs,operand);
            break;
        case '-':
            subtract(functions.funcs[i].parameters->valuefs,operand);
            break;
        case '*':
            multiply(functions.funcs[i].parameters->valuefs,operand);
            break;
        case '/':
            divide(functions.funcs[i].parameters->valuefs,operand);
            break;
        default:
            break;
        }
    }else{
        printf("Error! Undefined function %s\n",id);
    }
}

void callFunctionTwoParameter(char* id, char* parameter1, char* parameter2){
    int found = 0;
    int i=0;
    for(i=0;i< functions.size;i++){
        if(strcmp(functions.funcs[i].id,id)==0){
            found = 1;
            break;
        }
    }
    if(found){
        char operator = functions.funcs[i].explist[0][0]; 
        char *expression = strdup(functions.funcs[i].explist[0]);
        switch (operator){
        case '+':
            add(parameter1,parameter2);
            break;
        case '-':
            subtract(parameter1,parameter2);
            break;
        case '*':
            multiply(parameter1,parameter2);
            break;
        case '/':
            divide(parameter1,parameter2);
            break;
        default:
            break;
        }
    }
    else{
        printf("Error! Undefined function %s\n",id);
    }
}

int gcd(int a, int b) {
    while (b != 0) {
        unsigned int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char* add(const char* a, const char* b) {
    unsigned int numerator_a, denominator_a;
    unsigned int numerator_b, denominator_b;

    if (sscanf(a, "%ub%u", &numerator_a, &denominator_a) != 2 ||
        sscanf(b, "%ub%u", &numerator_b, &denominator_b) != 2) {
        return NULL;
    }

    unsigned int result_numerator = numerator_a * denominator_b + numerator_b * denominator_a;
    unsigned int result_denominator = denominator_a * denominator_b;

    unsigned int gcd_value = gcd(result_numerator, result_denominator);
    result_numerator /= gcd_value;
    result_denominator /= gcd_value;

    printf("Result: %ub%u\n", result_numerator, result_denominator);

    char result_str[32];
    snprintf(result_str, sizeof(result_str), "%ub%u", result_numerator, result_denominator);

    char* formatted_result = strdup(result_str);

    return formatted_result;
}

char* subtract(const char* a, const char* b){
    unsigned int numerator_a, denominator_a;
    unsigned int numerator_b, denominator_b;

    if (sscanf(a, "%ub%u", &numerator_a, &denominator_a) != 2 ||
        sscanf(b, "%ub%u", &numerator_b, &denominator_b) != 2) {
        return NULL;
    }

    int result_numerator = numerator_a * denominator_b - numerator_b * denominator_a;
    int result_denominator = denominator_a * denominator_b;

    int gcd_value = gcd(result_numerator, result_denominator);
    result_numerator /= gcd_value;
    result_denominator /= gcd_value;

    printf("Result: %db%d\n", result_numerator, result_denominator);

    char result_str[32];
    snprintf(result_str, sizeof(result_str), "%ub%u", result_numerator, result_denominator);

    char* formatted_result = strdup(result_str);

    return formatted_result;
}

char* multiply(const char* a, const char* b){
    unsigned int numerator_a, denominator_a;
    unsigned int numerator_b, denominator_b;

    if (sscanf(a, "%ub%u", &numerator_a, &denominator_a) != 2 ||
        sscanf(b, "%ub%u", &numerator_b, &denominator_b) != 2) {
        return NULL;
    }

    unsigned int result_numerator = numerator_a * numerator_b;
    unsigned int result_denominator = denominator_a * denominator_b;

    unsigned int gcd_value = gcd(result_numerator, result_denominator);
    result_numerator /= gcd_value;
    result_denominator /= gcd_value;

    printf("Result: %ub%u\n", result_numerator, result_denominator);

    char result_str[32]; 
    snprintf(result_str, sizeof(result_str), "%ub%u", result_numerator, result_denominator);

    char* formatted_result = strdup(result_str);

    return formatted_result;
}

char* divide(const char* a, const char* b){
    unsigned int numerator_a, denominator_a;
    unsigned int numerator_b, denominator_b;

    if (sscanf(a, "%ub%u", &numerator_a, &denominator_a) != 2 ||
        sscanf(b, "%ub%u", &numerator_b, &denominator_b) != 2) {
        return NULL;
    }
    
    unsigned int result_numerator = numerator_a * denominator_b;
    unsigned int result_denominator = denominator_a * numerator_b;

    unsigned int gcd_value = gcd(result_numerator, result_denominator);
    result_numerator /= gcd_value;
    result_denominator /= gcd_value;

    printf("Result: %ub%u\n", result_numerator, result_denominator);

    char result_str[32];
    snprintf(result_str, sizeof(result_str), "%ub%u", result_numerator, result_denominator);

    char* formatted_result = strdup(result_str);
    return formatted_result;
}

char* concatenate(const char* operator, const char* exp1, const char* exp2) {
    int size = strlen(operator) + strlen(exp1) + strlen(exp2) + 3; 
    char* result = malloc(size);
    if (result != NULL) {
        sprintf(result, "%s %s %s", operator, exp1, exp2);
    }
    return result;
}

#endif