%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
int line_count = 0;
%}

%%

\n          { line_count++;}
[ \t]+      { char_count += yyleng; }
[^\t\n ]+   { word_count++; char_count += yyleng; }

%%

int main()
{
    FILE *file = fopen("read.txt", "r");
    if (!file) {
        perror("Error opening read.txt");
        return 1;
    }

    /* Point Lex input to read.txt */
    yyin = file;

    yylex();

    fclose(file);

    printf("--- Results for read.txt ---\n");
    printf("Lines      : %d\n", line_count);
    printf("Words      : %d\n", word_count);
    printf("Characters : %d\n", char_count);

    return 0;
}

int yywrap()
{
    return 1;
}
