#include <stdio.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

struct frames {
    int content;
    int count;
};

int main() {
    int i, j, k, p, f, pf = 0, id = 0, cnt = 1, min;
    int page[MAX_PAGES];
    struct frames frame[MAX_FRAMES];

    printf("Enter the number of pages: ");
    scanf("%d", &p);
    
    printf("Enter the referencing string: ");
    for (i = 0; i < p; i++) {
        scanf("%d", &page[i]);
    }
    
    printf("Enter the number of frames: ");
    scanf("%d", &f);
    
    for (i = 0; i < f; i++) {
        frame[i].content = -1;
        frame[i].count = 0;
    }

    printf("\nReference String   |   Frames   |   Status\n");
    printf("------------------------------------------\n");

    for (i = 0; i < p; i++) {
        int hit = 0;
        printf("        %-9d  |", page[i]);

        for (j = 0; j < f; j++) {
            if (frame[j].content == page[i]) {
                hit = 1;
                frame[j].count = cnt++; 
                break;
            }
        }

        if (hit) {
            for (j = 0; j < f; j++) {
                if (frame[j].content != -1) {
                    printf(" %-2d", frame[j].content);
                } else {
                    printf(" - ");
                }
            }
            printf("  |   HIT\n");
        } else {
            if (id < f) {
                frame[id].content = page[i];
                frame[id].count = cnt++;
                id++;
            } else {
                min = 0;
                for (k = 1; k < f; k++) {
                    if (frame[k].count < frame[min].count) {
                        min = k;
                    }
                }
                frame[min].content = page[i];
                frame[min].count = cnt++;
            }
            pf++;

            for (j = 0; j < f; j++) {
                if (frame[j].content != -1) {
                    printf(" %-2d", frame[j].content);
                } else {
                    printf(" - ");
                }
            }
            printf("  |   MISS\n");
        }
    }

    printf("------------------------------------------\n");
    printf("\nTOTAL PAGE FAULTS: %d\n", pf);

    return 0;
}
