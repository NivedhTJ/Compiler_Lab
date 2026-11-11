#include <stdio.h>
#include <stdlib.h>

#define MAX_STATES 20

int nStates, nTransitions;
int adj[MAX_STATES][MAX_STATES];
int eClosure[MAX_STATES][MAX_STATES];

void findEClosure(int state) {
    int stack[MAX_STATES], top = -1;
    int visited[MAX_STATES] = {0};

    stack[++top] = state;
    visited[state] = 1;
    eClosure[state][state] = 1;

    while (top >= 0) {
        int u = stack[top--];

        for (int v = 0; v < nStates; v++) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = 1;
                eClosure[state][v] = 1;
                stack[++top] = v;
            }
        }
    }
}

int main() {
    int u, v;
    char symbol;

    printf("Enter number of states: ");
    if (scanf("%d", &nStates) != 1) return 1;

    printf("Enter number of transitions: ");
    if (scanf("%d", &nTransitions) != 1) return 1;

    printf("Enter transitions (from_state to_state symbol) [Use 'e' for epsilon]:\n");
    for (int i = 0; i < nTransitions; i++) {
        scanf("%d %d %c", &u, &v, &symbol);
        if (symbol == 'e' || symbol == 'E') {
            adj[u][v] = 1;
        }
    }

    for (int i = 0; i < nStates; i++) {
        findEClosure(i);
    }

    printf("\n--- Epsilon Closures ---\n");
    for (int i = 0; i < nStates; i++) {
        printf("e-closure(q%d) = { ", i);
        for (int j = 0; j < nStates; j++) {
            if (eClosure[i][j]) {
                printf("q%d ", j);
            }
        }
        printf("}\n");
    }

    return 0;
}
