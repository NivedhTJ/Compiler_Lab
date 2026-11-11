/* #include <stdio.h>

int n, t;
int adj[20][20], cl[20][20];

void dfs(int s, int u) {
    cl[s][u] = 1;                       // u is reachable from s
    for (int v = 0; v < n; v++)
        if (adj[u][v] && !cl[s][v])
            dfs(s, v);
}

int main() {
    int u, v;
    char c;

    printf("Enter num of states and transitions");
    scanf("%d %d", &n, &t);
    while (t--) {
        scanf("%d %d %c", &u, &v, &c);
        if (c == 'e') adj[u][v] = 1;
    }

    for (int i = 0; i < n; i++) {
        dfs(i, i);
        printf("e-closure(q%d) = { ", i);
        for (int j = 0; j < n; j++)
            if (cl[i][j]) printf("q%d ", j);
        printf("}\n");
    }
    return 0;
} */

#include <stdio.h>

int n, t;
int cl[20][20];

int main() {
    int u, v, i, j, k;
    char c;

    printf("Enter num of states and transitions: ");
    scanf("%d %d", &n, &t);

    while (t--) {
        scanf("%d %d %c", &u, &v, &c);
        if (c == 'e') cl[u][v] = 1;       // store directly in cl
    }

    for (i = 0; i < n; i++)
        cl[i][i] = 1;                     // each state reaches itself

    for (k = 0; k < n; k++)               // k MUST be the outermost loop
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                cl[i][j] = cl[i][j] || (cl[i][k] && cl[k][j]);

    for (i = 0; i < n; i++) {
        printf("e-closure(q%d) = { ", i);
        for (j = 0; j < n; j++)
            if (cl[i][j]) printf("q%d ", j);
        printf("}\n");
    }
    return 0;
}