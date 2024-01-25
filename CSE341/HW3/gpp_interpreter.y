%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #include "yacc_helper.h"        
%}

%union{
    char *string; // For identifiers
    char *valuef;
}

%token <string> IDENTIFIER
%token <valuef> VALUEF;
%token KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL KW_LIST KW_APPEND KW_CONCAT KW_SET KW_DEF KW_FOR KW_IF KW_EXIT KW_LOAD KW_DISPLAY KW_TRUE KW_FALSE
%token OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_COMMA COMMENT

%start START

%type <valuef> EXP
%type <string> INPUT
%type <valuef> FUNCTION

%%

START: |
    EXP START| // In order to get sequential inputs, I added START to the CFG's.
    FUNCTION START| 
    OP_OP KW_EXIT OP_CP {printf("Terminating...\n"); exit(0);}

EXP:
    OP_OP OP_PLUS EXP EXP OP_CP {$$ = add($3, $4); $$ = concatenate("+",$3,$4);} |
    OP_OP OP_MINUS EXP EXP OP_CP {$$ = subtract($3,$4); $$ = concatenate("-",$3,$4);} |
    OP_OP OP_MULT EXP EXP OP_CP {$$ = multiply($3,$4); $$ = concatenate("*",$3,$4);} | 
    OP_OP OP_DIV EXP EXP OP_CP {$$ = divide($3,$4); $$ = concatenate("/",$3,$4);} |
    OP_OP IDENTIFIER EXP OP_CP {callFunctionOneParameter($2,$3);} |
    OP_OP IDENTIFIER EXP EXP OP_CP {callFunctionTwoParameter($2,$3,$4);} |
    OP_OP IDENTIFIER EXP EXP EXP OP_CP {printf("id exp exp exp\n");} | // This is never used since there is no function declaration with 3 parameters
    OP_OP KW_IF EXP OP_CP {} |
    VALUEF {strcpy($$,$1);} |  
    IDENTIFIER {{strcpy($$,$1);}};

FUNCTION:
    OP_OP KW_DEF IDENTIFIER EXP OP_CP {defineFunction($3,$4);}|
    OP_OP KW_DEF IDENTIFIER IDENTIFIER EXP OP_CP {defineFunctionWithParameters($3,$5,$4,NULL);}|
    OP_OP KW_DEF IDENTIFIER IDENTIFIER IDENTIFIER EXP OP_CP {defineFunctionWithParameters($3,$6,$4,$5);};
%%


int main(int argc, char* argv[]) {
    if (argc == 1){
        printf("Type (exit) for exit\n");
        printf("Enter your input\n");
    }
    else if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL)
        {
            printf("File not found\n");
            return 0;
        }
    }
    else{
        printf("Too many arguments\n");
        printf("Usage: ./gpp_interpreter || ./gpp_interpreter <filename>");
        return 0;
    }
    identifiers.ids = NULL;
    identifiers.size = 0;
    functions.size=0;
    functions.funcs=NULL;
    yyparse();
}