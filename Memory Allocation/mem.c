#include<stdio.h>
#include<stdlib.h>

void firstfit(int n, int M[n]) {
    int m;
    printf("Num of Processes: ");
    scanf("%d", &m);

    int B[m], MA[n];

    for (int i = 0; i < n; i++) {
        MA[i] = -1; //  init the fill Array with 0
    }

    printf("# BLOCKS -> ");
    for (int j = 0; j < n; j++) {
        printf("[ \033[1;32m%d\033[0m ]", M[j]);
    }
    printf("\n\n");

    for (int i = 0; i < m; i++) {
        int val;
        printf("REQ: ");
        scanf("%d", &val);
        int choosen = -1;
        for (int j = 0; j < m; j++) {
            if (MA[j] != -1) {
                if (val <= MA[j]) {
                    int maJOld = MA[j];
                    MA[j] = MA[j] - val;
                    printf("\nAllocated %dK from %dK Block", val, maJOld);
                    choosen = 0;
                    break;
                } else {
                    continue;
                }
            }
            if (val <= M[j]) {
                MA[j] = M[j] - val;
                printf("\nAllocated %dK from %dK Block", val, M[j]);
                choosen = j;
                break;
            }
        }

        if (choosen == -1) {
            printf("\nFailed, No Suitable Free Block.");
            i = i - 1;
        }


        printf("\n# --> PRO: ");
        for (int j = 0; j < n; j++) {
            if (MA[j] == -1) {
                printf("[ - ]");
            } else {
                printf("[ P%d ]", i);
            }
            if (MA[j] != -1) {
                printf("[ R ]");
            }
        }
        printf("\n# --> PRO: ");
        for (int j = 0; j < n; j++) {
            if (MA[j] == -1) {
                printf("[ \033[1;32m%d\033[0m ]", M[j]);
            } else {
                printf("[ \033[1;31m%d\033[0m ]", M[j] - MA[j]);
            }
            if (MA[j] != -1) {
                printf("[ \033[1;32m%d\033[0m ]", MA[j]);
            }
        }


        printf("\n");
    }
}

void bestFit(int n, int X[]) {
    int M[n];

    for (int i = 0; i < n; i++) {
        M[i] = X[i];
    }

    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    int A[n];
    for (int i = 0; i < n; i++) {
        A[i] = M[i];
    }

    printf("# BLOCKS -> ");
    for (int j = 0; j < n; j++) {
        printf("[ \033[1;32m%d\033[0m ]", M[j]);
    }
    printf("\n\n");

    int processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i]);

        int bestFitIdx = -1;
        for (int j = 0; j < n; j++) {
            if (M[j] >= processes[i]) {
                if (bestFitIdx == -1 || M[j] < M[bestFitIdx]) {
                    bestFitIdx = j;
                }
            }
        }

        if (bestFitIdx != -1) {
            printf("Process %d allocated to block of size %d\n", i + 1, M[bestFitIdx]);
            M[bestFitIdx] -= processes[i];
        } else {
            printf("Process %d cannot be allocated\n", i + 1);
        }

        printf("# MEM -->\n");
        for (int k = 0; k < n; k++) {
            printf("<[");
            if (A[k] - M[k] == 0) {
                printf(" \033[1;32m%d\033[0m ", M[k]);
            } else {
                printf(" \033[1;32m%d\033[0m ", M[k]);
            }
            if (A[k] - M[k] != 0) {
                printf(" \033[1;31m%d\033[0m ", A[k] - M[k]);
            }
            printf("]>");
        }
        printf("\n\n");
    }
}

void worstFit(int n, int X[]) {
    int M[n];

    for (int i = 0; i < n; i++) {
        M[i] = X[i];
    }

    int numProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    int A[n];
    for (int i = 0; i < n; i++) {
        A[i] = M[i];
    }

    int processes[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i]);

        int worstFitIdx = -1;
        for (int j = 0; j < n; j++) {
            if (M[j] >= processes[i]) {
                if (worstFitIdx == -1 || M[j] > M[worstFitIdx]) {
                    worstFitIdx = j;
                }
            }
        }

        if (worstFitIdx != -1) {
            printf("Process %d allocated to block of size %d\n", i + 1, M[worstFitIdx]);
            M[worstFitIdx] -= processes[i];
        } else {
            printf("Process %d cannot be allocated\n", i + 1);
        }

        printf("# MEM -->\n");
        //  for (int k = 0; k < n; k++) {
        for (int k = 0; k < n; k++) {
            printf("<[");
            if (A[k] - M[k] == 0) {
                printf(" \033[1;32m%d\033[0m ", M[k]);
            } else {
                printf(" \033[1;32m%d\033[0m ", M[k]);
            }
            if (A[k] - M[k] != 0) {
                printf(" \033[1;31m%d\033[0m ", A[k] - M[k]);
            }
            printf("]>");
        }
        //}
        printf("\n\n");
    }
}




int main() {
    printf("Enter Num of FreeMem: ");
    int n, m;
    scanf("%d", &n);
    int M[n];

    printf("Enter Mem Blocks: \n");
    for (int i = 0; i < n; i++) {
        printf("#B%d: ", i);
        scanf("%d", &M[i]);
    }

    int ch;

    while (1) {
        printf("\n----Choose Allocation Algo----\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n\nEnter Choice: ");
        scanf("%d", &ch);

        switch (ch) {
        case 1:
            firstfit(n, M);
            break;
        case 2:
            bestFit(n, M);
            break;
        case 3:
            worstFit(n, M);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice (Try Again)\n");
        }
    }
}


