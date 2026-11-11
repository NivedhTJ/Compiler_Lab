#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *input = fopen("input.txt", "r"), *output = fopen("output.txt", "w");
    if (!input || !output) return 1;

    int l = 1, t = 0, i;
    char ch, str[20];
    char keyword[][10] = {"int", "main", "if", "else", "do", "while","void","char"};
    int num_keywords = sizeof(keyword) / sizeof(keyword[0]);

    fprintf(output, "Line no. \t Token no. \t\t Token \t\t Lexeme\n\n");

    while ((ch = fgetc(input)) != EOF) {
        char *type = NULL;

        if (ch == '\n') {
            l++;
            continue;
        }

        if (strchr("+-*/", ch)) {
            type = "Operator";
            sprintf(str, "%c", ch);
        } 
        else if (strchr(";{}()?@!%", ch)) {
            type = "Special symbol";
            sprintf(str, "%c", ch);
        } 
        else if (isdigit(ch)) {
            type = "Digit";
            sprintf(str, "%c", ch);
        } 
        else if (isalpha(ch)) {
            i = 0;
            while (isalnum(ch)) {
                str[i++] = ch;
                ch = fgetc(input);
            }
            str[i] = '\0';
            ungetc(ch, input);

            type = "Identifier";
            for (int j = 0; j < num_keywords; j++) {
                if (strcmp(str, keyword[j]) == 0) {
                    type = "Keyword";
                    break;
                }
            }
        }

        if (type) {
            fprintf(output, "%7d\t\t %7d\t\t %-15s %s\n", l, t++, type, str);
        }
    }

    fclose(input); fclose(output);
    return 0;
}
