%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *s);
%}

%token LETTER DIGIT

%%

identifier:
      LETTER
    | identifier LETTER
    | identifier DIGIT
    ;

%%

int main()
{
    printf("Enter an identifier: ");

    if (yyparse() == 0)
        printf("Valid identifier\n");
    else
        printf("Invalid identifier\n");

    return 0;
}

int yyerror(char *s)
{
    return 1;
}

