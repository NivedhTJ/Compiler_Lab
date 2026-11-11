%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | '-' expr %prec UMINUS
    | NUMBER
    ;

%%

int main()
{
    printf("Enter an arithmetic expression: ");

    if (yyparse() == 0)
        printf("Valid arithmetic expression\n");
    else
        printf("Invalid arithmetic expression\n");

    return 0;
}

int yyerror(char *s)
{
    return 0;
}

