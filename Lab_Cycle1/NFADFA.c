#include <stdio.h>
#include <stdlib.h>

#define MAX_NFA_STATES 10
#define MAX_DFA_STATES 20

int nNFA, nDFA = 0;
int nfaTable[MAX_NFA_STATES][2][MAX_NFA_STATES];
int dfaStates[MAX_DFA_STATES][MAX_NFA_STATES];
int dfaTable[MAX_DFA_STATES][2];

int nfaFinal[MAX_NFA_STATES] = {0};

int isSameSet(int *set1, int *set2) {
    for (int i = 0; i < nNFA; i++) {
        if (set1[i] != set2[i]) return 0;
    }
    return 1;
}

int findDFAState(int *set) {
    for (int i = 0; i < nDFA; i++) {
        if (isSameSet(dfaStates[i], set)) return i;
    }
    return -1;
}

void convertNFAtoDFA() {
    int startState[MAX_NFA_STATES] = {0};
    startState[0] = 1;

    for (int i = 0; i < nNFA; i++) dfaStates[0][i] = startState[i];
    nDFA = 1;

    for (int i = 0; i < nDFA; i++) {
        for (int sym = 0; sym < 2; sym++) {
            int moveSet[MAX_NFA_STATES] = {0};

            for (int q = 0; q < nNFA; q++) {
                if (dfaStates[i][q]) {
                    for (int nextQ = 0; nextQ < nNFA; nextQ++) {
                        if (nfaTable[q][sym][nextQ]) {
                            moveSet[nextQ] = 1;
                        }
                    }
                }
            }

            int isEmpty = 1;
            for (int k = 0; k < nNFA; k++) {
                if (moveSet[k]) {
                    isEmpty = 0;
                    break;
                }
            }

            if (isEmpty) {
                dfaTable[i][sym] = -1;
            } else {
                int existingIdx = findDFAState(moveSet);
                if (existingIdx == -1) {
                    for (int k = 0; k < nNFA; k++)
                        dfaStates[nDFA][k] = moveSet[k];

                    dfaTable[i][sym] = nDFA;
                    nDFA++;
                } else {
                    dfaTable[i][sym] = existingIdx;
                }
            }
        }
    }
}

void printDFAStateSet(int *set) {
    printf("{");
    int first = 1;

    for (int i = 0; i < nNFA; i++) {
        if (set[i]) {
            if (!first) printf(",");
            printf("q%d", i);
            first = 0;
        }
    }

    if (first) printf("Empty");
    printf("}");
}

int isDFAFinalState(int dfaState) {
    for (int i = 0; i < nNFA; i++) {
        if (dfaStates[dfaState][i] && nfaFinal[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int transitions, u, v;
    char sym;

    printf("Enter number of NFA states: ");
    if (scanf("%d", &nNFA) != 1) return 1;

    printf("Enter number of transitions: ");
    if (scanf("%d", &transitions) != 1) return 1;

    printf("Enter transitions (from_state to_state symbol['a' or 'b']):\n");
    for (int i = 0; i < transitions; i++) {
        scanf("%d %d %c", &u, &v, &sym);
        if (sym == 'a') nfaTable[u][0][v] = 1;
        else if (sym == 'b') nfaTable[u][1][v] = 1;
    }

    int nFinal, finalState;

    printf("Enter number of final states in NFA: ");
    scanf("%d", &nFinal);

    printf("Enter the final states: ");
    for (int i = 0; i < nFinal; i++) {
        scanf("%d", &finalState);
        nfaFinal[finalState] = 1;
    }

    convertNFAtoDFA();

    printf("\n--- DFA Transition Table ---\n");
    printf("DFA State\tSubset\t\tOn 'a'\t\tOn 'b'\n");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < nDFA; i++) {
        printf("D%d\t\t", i);
        printDFAStateSet(dfaStates[i]);
        printf("\t\t");

        if (dfaTable[i][0] != -1) printf("D%d", dfaTable[i][0]);
        else printf("-");

        printf("\t\t");

        if (dfaTable[i][1] != -1) printf("D%d", dfaTable[i][1]);
        else printf("-");

        printf("\n");
    }

    printf("\nDFA Final States: ");

    for (int i = 0; i < nDFA; i++) {
        if (isDFAFinalState(i)) {
            printf("D%d ", i);
        }
    }

    printf("\n");

    return 0;
}
