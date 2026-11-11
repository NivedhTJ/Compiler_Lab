#include <stdio.h>
#include <string.h>

char stack[30], input[30];
int top = 0; // Tracks the top of the stack

void print_status(const char *action) {
    printf("$%-15s\t%-15s$\t%s\n", stack, input, action);
}

void check_and_reduce() {
    // Check from the top of the stack backwards
    
    // Rule 1: E -> id
    if (top >= 2 && stack[top - 2] == 'i' && stack[top - 1] == 'd') {
        stack[top - 2] = 'E';
        stack[top - 1] = '\0';
        top -= 1;
        print_status("REDUCE TO E -> id");
        check_and_reduce(); // Recursively check if further reductions are possible
    }
    // Rule 2: E -> E + E
    else if (top >= 3 && stack[top - 3] == 'E' && stack[top - 2] == '+' && stack[top - 1] == 'E') {
        stack[top - 3] = 'E';
        stack[top - 2] = '\0';
        top -= 2;
        print_status("REDUCE TO E -> E+E");
        check_and_reduce();
    }
    // Rule 3: E -> E * E
    else if (top >= 3 && stack[top - 3] == 'E' && stack[top - 2] == '*' && stack[top - 1] == 'E') {
        stack[top - 3] = 'E';
        stack[top - 2] = '\0';
        top -= 2;
        print_status("REDUCE TO E -> E*E");
        check_and_reduce();
    }
    // Rule 4: E -> (E)
    else if (top >= 3 && stack[top - 3] == '(' && stack[top - 2] == 'E' && stack[top - 1] == ')') {
        stack[top - 3] = 'E';
        stack[top - 2] = '\0';
        top -= 2;
        print_status("REDUCE TO E -> (E)");
        check_and_reduce();
    }
}

int main() {
    puts("GRAMMAR:\nE -> E+E\nE -> E*E\nE -> (E)\nE -> id\n");
    printf("Enter input string: ");
    scanf("%s", input);

    printf("\n%-16s\t%-16s\t%s\n", "STACK", "INPUT", "ACTION");
    print_status("INITIAL");

    int len = strlen(input);
    int i = 0;

    while (i < len) {
        // Shift 'id' together if encountered
        if (input[i] == 'i' && input[i + 1] == 'd') {
            stack[top++] = 'i';
            stack[top++] = 'd';
            stack[top] = '\0';
            input[i] = ' ';
            input[i + 1] = ' ';
            i += 2;
            print_status("SHIFT id");
        } 
        // Shift operators/parentheses
        else {
            stack[top++] = input[i];
            stack[top] = '\0';
            input[i] = ' ';
            i++;
            print_status("SHIFT symbol");
        }
        
        // Try to reduce after every shift
        check_and_reduce();
    }

    // Final Validation
    if (strcmp(stack, "E") == 0) {
        printf("\nSUCCESS: String Accepted!\n");
    } else {
        printf("\nFAILURE: String Rejected.\n");
    }

    return 0;
}
