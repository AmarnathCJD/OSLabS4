#include <stdio.h>

#define NUM_PROC 5
#define NUM_RES 3

int alloc[NUM_PROC][NUM_RES], max[NUM_PROC][NUM_RES], avail[NUM_RES];

void read(int n, int m) {
    for (int i = 0; i < n; i++) {
        printf("Enter allocation for P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Enter max for P%d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    
}

void print(int n, int m) {
    printf("\n -> Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\n");
    }

    printf("\n -> Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    // print need matrix

    printf("\n -> Need matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", max[i][j] - alloc[i][j]);
        }
        printf("\n");
    }

    printf("\n -> Available resources: ");
    for (int i = 0; i < m; i++) {
        printf("%d ", avail[i]);
    }
    printf("\n\n");
}

// P0, P1, P2, P3, P4; Example
// {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}}; -> Allocation matrix
// {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}} -> Max resources
// {3, 3, 2} -> Available resources

int main() {
    int n = NUM_PROC, m = NUM_RES, i, j, k;
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &n, &m);

    read(n, m);
    print(n, m);

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    int y = 0;
    for (k = 0; k < 5; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {

                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;

    for (int i = 0;i < n;i++) {
        if (f[i] == 0) {
            flag = 0;
            printf("The following system is not safe");
            break;
        }
    }

    if (flag == 1) {
        printf("Following is the SAFE Sequence\n");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", ans[i]);
        printf(" P%d", ans[n - 1]);
    }

    printf("\n");


    return (0);
}