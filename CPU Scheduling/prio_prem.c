#include <stdio.h>

typedef struct {
    int pid, flag, at, bt, nat, nbt, wt, tt, rt, priority;
} process;

void swap(process p[], int j, int i) {
    process temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

void sort(process p[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (p[j].priority > p[j + 1].priority) {
                swap(p, j, j + 1);
            }
        }
    }
}

int pRemain(process arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i].flag == 0)
            return 1;
    }
    return 0;
}

int getIndex(process arr[], int n, int t) {
    for (int i = 0; i < n; i++) {
        if (arr[i].nat <= t && arr[i].flag == 0)
            return i;
    }
    return -1;
}

int nextAt(process arr[], int n, int t) {
    int min = 999999;
    int index;
    for (int i = 0; i < n; i++) {
        if (arr[i].nat > t && arr[i].nat < min && arr[i].flag == 0) {
            index = i;
            min = arr[i].nat;
        }
    }
    return arr[index].nat;
}

void sortpid(process p[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (p[j].pid > p[j + 1].pid)
                swap(p, j, j + 1);
        }
    }
}

void display(process p[], int n) {
    printf("Process AT BT CT TAT WT\n");
    int wt = 0, tt = 0;
    for (int i = 0; i < n; i++) {
        printf("  P%d    %2d %2d %2d %2d %2d\n", p[i].pid, p[i].at, p[i].bt, p[i].tt + p[i].at, p[i].wt, p[i].tt);
        wt += p[i].wt;
        tt += p[i].tt;
    }
    float avgtt = (float)tt / n;
    float avgwt = (float)wt / n;
    printf("Average waiting time = %.2f\nAverage turnaround time = %.2f\n", avgwt, avgtt);
}

typedef struct {
    int pid;
    int st;
    int ct;
} ganttproc;

void ganttChart(ganttproc d[], int n) {
    printf("\n\nGantt Chart\n");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("|");
        printf("   %d\t", d[i].pid);
    }
    printf(" |");
    printf("\n---------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", d[i].st);
    }
    printf("%d\t", d[n - 1].ct);
    printf("\n\n");
}

void priorityPreemptive(process arr[], int n) {
    ganttproc d[100];
    int gi = 0;
    int index;
    int t = 0;
    printf(" |");
    while (pRemain(arr, n) == 1) {
        index = getIndex(arr, n, t);
        if (index == -1) {
            t = nextAt(arr, n, t);
            if (d[gi - 1].pid != -1) {
                d[gi].pid = -1;
                if (t == 1)
                    d[gi].st = 0;
                else
                    d[gi].st = t - 1;
                gi++;
            } else {
                d[gi - 1].ct = t;
            }
        } else {
            if (arr[index].nbt == arr[index].bt)
                arr[index].rt = t - arr[index].at;
            arr[index].nbt--;
            t++;
            printf(" P%d |%d", arr[index].pid, t);
            if (d[gi - 1].pid != arr[index].pid) {
                d[gi].pid = arr[index].pid;
                d[gi].st = t - 1;
                gi++;
            } else {
                d[gi - 1].ct = t;
            }
            if (arr[index].nbt == 0) {
                arr[index].flag = 1;
                arr[index].tt = t - arr[index].at;
                arr[index].wt = arr[index].tt - arr[index].bt;
            }
            arr[index].nat = t;
        }
        sort(arr, n);
    }
    printf("\n");
    sortpid(arr, n);
    printf("\n");
    ganttChart(d, gi);
    display(arr, n);
}

void main() {
    int n;
    printf("Priority Preemptive Scheduling\n");
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process arr[n];
    printf("Enter the arrival time, burst time, and priority of each process\n");
    for (int i = 0; i < n; i++) {
        printf("P%d : ", i + 1);
        scanf("%d %d %d", &arr[i].at, &arr[i].bt, &arr[i].priority);
        arr[i].flag = 0;
        arr[i].pid = i + 1;
        arr[i].nat = arr[i].at;
        arr[i].nbt = arr[i].bt;
    }
    priorityPreemptive(arr, n);
}