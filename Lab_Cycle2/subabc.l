%{
#include <stdio.h>
%}

%%

abc     { printf("ABC"); }
.|\n    { printf("%s", yytext); }

%%

int main()
{
    printf("Enter input string: ");
    fflush(stdout);

    yylex();

    return 0;
}

int yywrap()
{
    return 1;
}
