#include <stdio.h>
#include <string.h>

int q[100], front = -1, rear = -1;

struct process {
    char name[20];
    int at, tt, bt, wt, status, left, ct;
} p[20], temp;

struct done {
    char name[20];
    int st, ct;
} d[20];

void enqueue(int j) {
    if (front == -1 && rear == -1) {
        front++;
    }
    rear++;
    q[rear] = j;
}

int dequeue() {
    int item;
    item = q[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front++;
    }
    return (item);
}

void printq() {
    if (front == -1 && q[front] == 0 && front == rear) {
        printf("Queue Empty");
        return;
    }
    for (int i = front; i <= rear; i++) {
        printf("%d, ", q[i]);
    }
}

void DISPLAY(int n, int num) {
    int i = 0;

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


int main() {
    int n, i, j, idle = 0, k, num, ls, t;
    float avwt = 0, avtt = 0;
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
        p[i].left = p[i].bt;
        p[i].status = 0;
    }

    printf("\nQuantum : ");
    scanf("%d", &t);

    for (i = 0, num = 0, ls = 0; ls < n;) {
        for (j = 0; j < n; j++) {
            if (p[j].status == 0 && p[j].at <= i) {
                enqueue(j);
                p[j].status = 1;
            }
        }
        if (idle == 0 && front == -1) {
            strcpy(d[num].name, "-");
            d[num].st = i;
            idle = 1;
            i++;
        } else if (front != -1) {
            if (idle == 1) {
                d[num].ct = i;
                idle = 0;
                num++;
            }
            k = dequeue();
            d[num].st = i;
            strcpy(d[num].name, p[k].name);
            if (p[k].left <= t) {
                d[num].ct = i + p[k].left;
                p[k].ct = d[num].ct;
                i = d[num].ct;
                p[k].tt = i - p[k].at;
                p[k].wt = p[k].tt - p[k].bt;
                p[k].status = 2;
                ls++;
                num++;
            } else if (p[k].left > t) {
                d[num].ct = i + t;
                i = d[num].ct;
                p[k].left = p[k].left - t;
                num++;
                for (j = 0; j < n; j++) {
                    if (p[j].status == 0 && p[j].at <= i) {
                        enqueue(j);
                        p[j].status = 1;
                    }
                }
                enqueue(k);
            }
        } else {
            i++;
        }

        printf("\nJOB QUEUE: [");
        printq();
        printf("]");
        DISPLAY(n, num);
    }

    printf("\nSn  Name\tAT     \tBT     \tCT     \tWT     \tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d.  %s\t\t%d\t%d\t%d\t%d\t%d\n", i, p[i].name, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tt);
    }

    printf("\n\n");
}