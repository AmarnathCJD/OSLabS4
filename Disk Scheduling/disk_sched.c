#include<stdio.h>
int track[20];
int tracks, head, up_bound = 200, low_bound = 0;

int sort() {
    int i, j, pos;
    for (i = 0; i < tracks; i++) {
        for (j = 0; j < tracks - i; j++) {
            if (track[j] > track[j + 1]) {
                int temp = track[j];
                track[j] = track[j + 1];
                track[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < tracks; i++) {
        if (track[i] == head) {
            pos = i;
            break;
        }
    }
    return pos;
}

void fcfs() {
    int i, dist = 0;
    printf("Service Order: %d ", head);
    for (i = 1; i < tracks; i++) {
        if (track[i] > track[i - 1]) {
            dist += (track[i] - track[i - 1]);
            printf("%d ", track[i]);
        } else {
            dist += (track[i - 1] - track[i]);
            printf("%d ", track[i]);
        }
    }
    printf("\nDistance = %d\n", dist);
}

void cscan() {
    int i, pos, dist = 0;
    pos = sort();
    printf("Service Order: %d ", head);
    for (i = pos + 1; i <= tracks; i++) {
        dist += track[i] - track[i - 1];

        printf("%d ", track[i]);
    }
    dist += up_bound - track[tracks];
    dist += up_bound - low_bound;
    dist += low_bound + track[0];
    printf("%d %d ", up_bound, low_bound);
    for (i = 1; i < pos; i++) {
        dist += track[i] - track[i - 1];
        printf("%d ", track[i]);
    }
    printf("\nDistance = %d\n", dist);
}

void scan() {
    int i, pos, dist = 0;
    pos = sort();
    printf("Service Order: %d ", head);
    for (i = pos + 1; i <= tracks; i++) {
        dist += track[i] - track[i - 1];
        printf("%d ", track[i]);
    }
    dist += up_bound - track[tracks];
    dist += up_bound - track[pos - 1];
    printf("%d %d ", up_bound, track[pos - 1]);
    for (i = pos - 2; i > 0; i--) {
        dist += track[i + 1] - track[i];
        printf("%d ", track[i]);
    }
    printf("\nDistance = %d\n", dist);
}

void main() {
    // 0-199 tracks
    
    int i, ch = 0;
    printf("Enter the number of tracks: ");
    scanf("%d", &tracks);
    printf("Enter the value for each track: ");
    for (i = 0; i < tracks; i++) {
        scanf("%d", &track[i + 1]);
    }
    tracks++;
    printf("Enter the head position: ");
    scanf("%d", &head);
    track[0] = head;

    while (ch != 4) {
        printf("\n---MENU---\n 1. FCFS\n 2. SCAN\n 3. C-SCAN\nEnter your choice : ");
            scanf("%d", &ch);
        switch (ch) {
        case 1:
            fcfs();
            break;
        case 2:
            scan();
            break;
        case 3:
            cscan();
            break;
        case 4:
            printf("Terminating.\n");
        }
    }
}