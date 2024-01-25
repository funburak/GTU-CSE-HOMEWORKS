%{
    #include <stdio.h>
    #include <stdlib.h>

    #include "gpp_interpreter.h"
%}

COMMENT [;]{2}.*
IDENTIFIER [a-zA-Z][a-zA-Z0-9]*
VALUEF [1-9][0-9]*+[b]+[1-9][0-9]*


%%
    /* OPERATORS */

[+] {return OP_PLUS;}
[-] {return OP_MINUS;}
[/] {return OP_DIV;}
[*] {return OP_MULT;}
[(] {return OP_OP;}
[)] {return OP_CP;}
[,] {return OP_COMMA;}

    /* KEYWORDS */

and {return KW_AND;}
or {return KW_OR;}
not {return KW_NOT;}
equal {return KW_EQUAL;}
less {return KW_LESS;}
nil {return KW_NIL;}
list {return KW_LIST;}
append {return KW_APPEND;}
concat {return KW_CONCAT;}
set {return KW_SET;}
def {return KW_DEF;}
for {return KW_FOR;}
if {return KW_IF;}
exit {return KW_EXIT;}
load {return KW_LOAD;}
display {return KW_DISPLAY;}
true {return KW_TRUE;}
false {return KW_FALSE;}

    /* ERRORS */
[1-9][0-9]*[a-zA-Z]+ {printf("SYNTAX_ERROR %s cannot be tokenized\n",yytext); exit(1);}

    /* any character inside two number except b will be considered as error. */
[1-9][0-9]*[^b][1-9][0-9]* {printf("Error! Undefined statement:%s\n",yytext); exit(1);}


{COMMENT} {return COMMENT;}
{IDENTIFIER} {yylval.string = strdup(yytext); return IDENTIFIER;}
{VALUEF} {yylval.valuef = strdup(yytext); return VALUEF;}

    /* ignore whitespaces, tabs and newlines */
[ ] {;}
[\t] {;}
[\n] {;}


%%
