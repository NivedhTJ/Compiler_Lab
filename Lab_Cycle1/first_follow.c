#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m, visited[26];
char a[10][10], f[10];

void add(char c) {
    for (int k = 0; k < m; k++) if (f[k] == c) return;
    f[m++] = c;
}

// Computes First of a character
void first(char c) {
    if (!isupper(c)) { add(c); return; }
    for (int i = 0; i < n; i++) {
        if (a[i][0] != c) continue;
        int j = 2;
        while (a[i][j]) {
            int old_m = m, has_eps = 0;
            first(a[i][j]);
            // Fast in-place set subtraction of epsilon '#'
            for (int k = old_m; k < m; k++) {
                if (f[k] == '#') {
                    has_eps = 1;
                    f[k--] = f[--m]; 
                }
            }
            if (!has_eps) break;
            j++;
        }
        if (!a[i][j]) add('#');
    }
}

// Computes Follow of a non-terminal
void follow(char c) {
    if (visited[c - 'A']) return;
    visited[c - 'A'] = 1;

    if (a[0][0] == c) add('$');

    for (int i = 0; i < n; i++) {
        for (int j = 2; a[i][j]; j++) {
            if (a[i][j] != c) continue;
            int next_idx = j + 1;
            while (a[i][next_idx]) {
                char next_sym = a[i][next_idx];
                if (!isupper(next_sym)) {
                    add(next_sym);
                    break;
                }
                int old_m = m, has_eps = 0;
                first(next_sym);
                // Directly filter out epsilon from the added First elements
                for (int k = old_m; k < m; k++) {
                    if (f[k] == '#') {
                        has_eps = 1;
                        f[k--] = f[--m];
                    }
                }
                if (!has_eps) break;
                next_idx++;
            }
            if (!a[i][next_idx] && c != a[i][0]) {
                follow(a[i][0]);
            }
        }
    }
}

int main() {
    int z; char c;
    printf("Enter the no of productions:\n");
    scanf("%d", &n);
    printf("Use '#' for epsilon and uppercase for Non-Terminals (e.g., E=TR):\n");
    for (int i = 0; i < n; i++) scanf("%s", a[i]);
    
    do {
        printf("\nEnter non-terminal element: ");
        scanf(" %c", &c);
        
        m = 0; memset(f, 0, sizeof(f));
        first(c);
        printf("First(%c) = { ", c);
        for (int i = 0; i < m; i++) printf("%c ", f[i]);
        printf("}\n");
        
        m = 0; memset(f, 0, sizeof(f));
        memset(visited, 0, sizeof(visited));
        follow(c);
        printf("Follow(%c) = { ", c);
        for (int i = 0; i < m; i++) printf("%c ", f[i]);
        printf("}\n");
        
        printf("Continue(0/1)? ");
        scanf("%d", &z);
    } while (z == 1);
    return 0;
}
