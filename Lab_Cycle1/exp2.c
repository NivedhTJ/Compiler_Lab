#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i = 0, error = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void E()
{
    printf("E -> T E'\n");
    T();
    Eprime();
}

void Eprime()
{
    if (input[i] == '+')
    {
        printf("E' -> + T E'\n");
        i++;
        T();
        Eprime();
    }
    else if (input[i] == '-')
    {
        printf("E' -> - T E'\n");
        i++;
        T();
        Eprime();
    }
    else
    {
        printf("E' -> ε\n");
    }
}

void T()
{
    printf("T -> F T'\n");
    F();
    Tprime();
}

void Tprime()
{
    if (input[i] == '*')
    {
        printf("T' -> * F T'\n");
        i++;
        F();
        Tprime();
    }
    else if (input[i] == '/')
    {
        printf("T' -> / F T'\n");
        i++;
        F();
        Tprime();
    }
    else
    {
        printf("T' -> ε\n");
    }
}

void F()
{
    if (isalnum(input[i]))
    {
        printf("F -> id (%c)\n", input[i]);
        i++;
    }
    else if (input[i] == '(')
    {
        printf("F -> (E)\n");
        i++;
        E();

        if (input[i] == ')')
            i++;
        else
            error = 1;
    }
    else
    {
        error = 1;
    }
}

int main()
{
    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("\nProductions Used:\n\n");

    E();

    if (input[i] == '\0' && error == 0)
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}
