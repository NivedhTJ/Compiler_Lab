%{
#include <stdio.h>
#include <stdlib.h>
%}


DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
NUMBER      {DIGIT}+(\.{DIGIT}+)?
WS          [ \t\n]+


%%


"int"|"float"|"char"|"if"|"else"|"while"|"for"|"return" {
    printf("| %-18s | %-12s |\n", "KEYWORD", yytext);
}


"//".* ;
"/*"([^*]|\*+[^*/])*\*+"/" ;


{ID} {
    printf("| %-18s | %-12s |\n", "IDENTIFIER", yytext);
}


{NUMBER} {
    printf("| %-18s | %-12s |\n", "NUMBER", yytext);
}


"+"|"-"|"*"|"/"|"%" {
    printf("| %-18s | %-12s |\n", "ARITHMETIC OP", yytext);
}


"=="|"!="|"<="|">="|"<"|">" {
    printf("| %-18s | %-12s |\n", "RELATIONAL OP", yytext);
}


"=" {
    printf("| %-18s | %-12s |\n", "ASSIGNMENT OP", yytext);
}


";"|","|"("|")"|"{"|"}" {
    printf("| %-18s | %-12s |\n", "SPECIAL SYMBOL", yytext);
}


{WS} ;


. {
    printf("| %-18s | %-12s |\n", "UNKNOWN TOKEN", yytext);
}


%%


int yywrap() {
    return 1;
}


int main() {
    FILE *file = fopen("input.txt", "r");


    if (file == NULL) {
        printf("Cannot open input.txt\n");
        return 1;
    }


    yyin = file;


    printf("+--------------------+--------------+\n");
    printf("| %-18s | %-12s |\n", "TOKEN TYPE", "LEXEME");
    printf("+--------------------+--------------+\n");


    yylex();


    printf("+--------------------+--------------+\n");


    fclose(file);
    return 0;
}