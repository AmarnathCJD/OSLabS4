#include <stdio.h>
#include <string.h>

struct process {
    char name[20];
    int at, tt, bt, wt, status, ct;
} p[20], temp;

struct done {
    char name[20];
    int st, ct;
} d[20];

void main() {
    int n, i, j, ls, min, fnd, num, idle;
    printf("Enter Num PROC: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\n# PROC %d -->", i + 1);
        printf("\nName : ");
        scanf(" %s", p[i].name);
        printf("ArivalTime (AT): ");
        scanf("%d", &p[i].at);
        printf("BurstTime  (BT): ");
        scanf("%d", &p[i].bt);
        p[i].status = 0;
    }
    
    i = 0, num = 0, idle = 0;
    
    for (ls = 0; ls < n;) {
    	fnd = 0;
        for (j = 0; j < n; j++) {
            if (i >= p[j].at && p[j].status == 0) {
                if (fnd == 0) {
                    min = j;
                    fnd = 1;
                } else if (fnd != 0 && p[min].bt > p[j].bt) {
                    min = j;
                }
            }
        }
        
        if (idle == 0 && fnd == 0) {
            strcpy(d[num].name, "-");
            d[num].st = i;
            i++;
            idle = 1;
        } else if (fnd == 1) {
            if (idle == 1) {
                d[num].ct = i;
                num++;
                idle = 0;
            }
            strcpy(d[num].name, p[min].name);
            p[min].status = 1;
            d[num].st = i;
            d[num].ct = i + p[min].bt;
            i = d[num].ct;
            p[min].ct = d[num].ct;
            p[min].tt = p[min].ct - p[min].at;
            p[min].wt = p[min].tt - p[min].bt;
            num++;
            ls++;
        } else {
            i++;
        }
    }
    
    printf("\nSn  Name\tAT     \tBT     \tCT     \tWT     \tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d.  %s\t\t%d\t%d\t%d\t%d\t%d\n", i, p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
    }
    printf("\n\nG Chart ");
    printf("\n----------------------------------------------------------\n");
    for (i = 0; i < num; i++) {
        printf("|");
        printf("   %s\t", d[i].name);
    }
    printf(" |");
    printf("\n----------------------------------------------------------\n");
    for (i = 0; i < num; i++) {
        printf("%d\t", d[i].st);
    }
    printf("%d\t", d[num - 1].ct);
    printf("\n\n");
}
