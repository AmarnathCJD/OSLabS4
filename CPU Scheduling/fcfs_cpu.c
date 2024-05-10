#include <stdio.h>
#include <string.h>

struct process {
    char name[20];
    int at, tt, bt, wt, ct, status;
} p[20], temp;

struct done {
    char name[20];
    int st, ct;
} d[20];

int main() {
    int i, j, n, num, idle = 0;
    float avwt = 0;
    float avtt = 0;
    printf("Enter Num PROC: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("\n# PROC %d -->", i + 1);
        printf("\nName: ");
        scanf(" %s", p[i].name);
        printf("ArivalTime (AT): ");
        scanf("%d", &p[i].at);
        printf("BurstTime  (BT): ");
        scanf("%d", &p[i].bt);
        p[i].status = 0;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    i = 0, num = 0;


    for (j = 0;j < n;) {
        if (p[j].at <= i && p[j].status == 0) {
            if (idle == 1) {
                d[num].ct = i;
                num++;
                idle = 0;
            }
            strcpy(d[num].name, p[j].name);
            d[num].st = i;
            d[num].ct = i + p[j].bt;
            p[j].wt = d[num].st - p[j].at;
            p[j].tt = p[j].wt + p[j].bt;
            p[j].ct = d[num].ct;
            i = d[num].ct;
            p[j].status = 1;
            j++;
            num++;
        } else if (idle == 0) {
            strcpy(d[num].name, "-");
            d[num].st = i;
            i++;
            idle = 1;
        } else {
            i++;
        }
    }

    printf("\nSn  Name\tAT     \tBT     \tCT     \tWT     \tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d.  %s\t\t%d\t%d\t%d\t%d\t%d\n", i, p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
        avwt += p[i].wt;
        avtt += p[i].tt;
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
