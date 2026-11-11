#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Stack structure for operators and operands
char opStack[MAX];
int opTop = -1;

char argStack[MAX][10];
int argTop = -1;

int tempVarCount = 1;

void pushOp(char c)   { if (opTop < MAX-1) opStack[++opTop] = c; }
char popOp()          { if (opTop >= 0) return opStack[opTop--]; return '\0'; }
void pushArg(char *s) { if (argTop < MAX-1) strcpy(argStack[++argTop], s); }
void popArg(char *s)  { if (argTop >= 0) strcpy(s, argStack[argTop--]); }

// Function to check operator precedence
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Emit Three-Address Code instruction and push result variable
void generateTAC(char op) {
    char arg2[10], arg1[10], temp[10];
    
    popArg(arg2);
    popArg(arg1);
    
    // Create a temporary variable name (e.g., t1, t2)
    sprintf(temp, "t%d", tempVarCount++);
    
    // Print the Three-Address Code instruction
    printf("%s = %s %c %s\n", temp, arg1, op, arg2);
    
    // Push result temp variable back to operand stack
    pushArg(temp);
}

int main() {
    char expr[MAX];
    
    printf("Enter an infix expression (e.g., a+b*c): ");
    scanf("%s", expr);
    
    printf("\n--- Generated Three-Address Code (TAC) ---\n");
    
    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        
        // If character is an operand (variable or number)
        if (isalnum(ch)) {
            char str[2] = {ch, '\0'};
            pushArg(str);
        } 
                // If character is an operator
        else {
            while (opTop >= 0 && precedence(opStack[opTop]) >= precedence(ch)) {
                generateTAC(popOp());
            }
            pushOp(ch);
        }
    }
    
    // Process remaining operators in stack
    while (opTop >= 0) {
        generateTAC(popOp());
    }
    
    printf("------------------------------------------\n");
    
    return 0;
}


/*
#include <stdio.h>
#include <ctype.h>

char op[50];                 // operator stack
char arg[50][10];            // operand stack
int ot = -1, at = -1, t = 1;

int precedence(char o) {
    switch (o) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void gen() {
    char o = op[ot--];                                   // pop operator
    printf("t%d = %s %c %s\n", t, arg[at-1], o, arg[at]); // print TAC
    at--;                                                // pop 2, push 1
    sprintf(arg[at], "t%d", t++);                        // result goes in first slot
}

int main() {
    char e[50];
    scanf("%s", e);

    for (int i = 0; e[i]; i++) {
        char ch = e[i];
        if (isalnum(ch)) {                  // operand
            arg[++at][0] = ch;
            arg[at][1] = '\0';
        }
        else if (ch == '(') op[++ot] = ch;
        else if (ch == ')') {
            while (op[ot] != '(') gen();
            ot--;                           // discard '('
        }
        else {                              // operator
            while (ot >= 0 && prec(op[ot]) >= prec(ch)) gen();
            op[++ot] = ch;
        }
    }
    while (ot >= 0) gen();
    return 0;
}