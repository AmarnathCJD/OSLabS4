#include <stdio.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

struct frame {
    int content;
    int freq;
    int cnt;
};

int main() {
    int i, j, pg, fr, cnt, pf, min, id = 0;
    int page[MAX_PAGES];
    struct frame frames[MAX_FRAMES];

    printf("Enter the number of pages: ");
    scanf("%d", &pg);
    
    printf("Enter the page numbers: ");
    for (i = 0; i < pg; i++) {
        scanf("%d", &page[i]);
    }
    
    printf("Enter the number of frames: ");
    scanf("%d", &fr);
    
    for (i = 0; i < fr; i++) {
        frames[i].content = -1;
        frames[i].freq = 0;
        frames[i].cnt = 0;
    }

    printf("\nReference String   |   Frames   |   Status\n");
    printf("------------------------------------------\n");

    for (pf = 0, cnt = 1, i = 0; i < pg; i++) {
        printf("        %-9d  |", page[i]);
        int hit = 0;
        
        // Check for HIT
        for (j = 0; j < fr; j++) {
            if (frames[j].content == page[i]) {
                hit = 1;
                frames[j].freq++;
                break;
            }
        }
        
        if (hit) {
            printf(" ");
            for (j = 0; j < fr; j++) {
                if (frames[j].content != -1) {
                    printf(" %-2d", frames[j].content);
                } else {
                    printf(" - ");
                }
            }
            printf("  |   HIT\n");
        } else {
            printf(" ");
            if (id < fr) {
                // Empty slot available
                frames[id].content = page[i];
                frames[id].freq++;
                frames[id].cnt = cnt++;
                id++;
            } else {
                // LFU replacement logic
                min = 0;
                for (j = 0; j < fr; j++) {
                    if (frames[min].freq > frames[j].freq) {
                        min = j;
                    } else if (frames[min].freq == frames[j].freq && frames[min].cnt > frames[j].cnt) {
                        min = j;
                    }
                }
                frames[min].content = page[i];
                frames[min].freq = 1;
                frames[min].cnt = cnt++;
            }
            pf++;
            for (j = 0; j < fr; j++) {
                if (frames[j].content != -1) {
                    printf(" %-2d", frames[j].content);
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
