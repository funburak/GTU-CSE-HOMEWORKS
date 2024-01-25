%{
    /* DEFINITIONS */
%}

COMMENT [;]{2}.*
VALUEF [1-9][0-9]*+[b]+[1-9][0-9]*
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*


%%
    /* OPERATORS */

[+] {printf("OP_PLUS\n");}
[-] {printf("OP_MINUS\n");}
[/] {printf("OP_DIV\n");}
[*] {printf("OP_MULT\n");}
[(] {printf("OP_OP\n");}
[)] {printf("OP_CP\n");}
[,] {printf("OP_COMMA\n");}

    /* KEYWORDS */

and {printf("KW_AND\n");}
or {printf("KW_OR\n");}
not {printf("KW_NOT\n");}
equal {printf("KW_EQUAL\n");}
less {printf("KW_LESS\n");}
nil {printf("KW_NIL\n");}
list {printf("KW_LIST\n");}
append {printf("KW_APPEND\n");}
concat {printf("KW_CONCAT\n");}
set {printf("KW_SET\n");}
def {printf("KW_DEF\n");}
for {printf("KW_FOR\n");}
if {printf("KW_IF\n");}
exit {printf("KW_EXIT\n"); return 0;}
load {printf("KW_LOAD\n");}
display {printf("KW_DISPLAY\n");}
true {printf("KW_TRUE\n");}
false {printf("KW_FALSE\n");}

    /* ERRORS */
[1-9][0-9]*[a-zA-Z]+ {printf("SYNTAX_ERROR %s cannot be tokenized\n",yytext);}

    /* any character inside two number except b will be considered as error. */
[1-9][0-9]*[^b][1-9][0-9]* {printf("Error! Undefined statement:%s\n",yytext);}


{COMMENT} {printf("COMMENT\n");}
{VALUEF} {printf("VALUEF\n");}
{IDENTIFIER} {printf("IDENTIFIER\n");}

    /* ignore whitespaces, tabs and newlines */
[ ] {;}
[\t] {;}
[\n] {;}

%%


int yywrap() {}
int main(int argc, char **argv){
    if(argc == 1){
        printf("Type exit to terminate.\n");
    }
    else if(argc == 2){
        FILE *fp;
        fp = fopen(argv[1],"r");
        yyin = fp;
    }
    yylex();
    return 0;
}
