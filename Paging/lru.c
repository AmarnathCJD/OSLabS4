#include<stdio.h>
#include<stdlib.h>

struct str {
    int c;
    int e;
    int p;
};

void main() {
    struct str fr[100];

    int n, m;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the number of frames: ");
    scanf("%d", &m);

    int pg[100] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

    for (int i = 0; i<m; i++) {
        fr[i].e = 0;
        fr[i].p = -1;
        fr[i].c = -1;
    }

    int pos = 0, h = 0, mz = 0;

    for (int i = 0; i<n; i++) {
        int found = -1;
        for (int j = 0; j<m; j++) {
            if (fr[j].c == pg[i]) {
                found = j;
                fr[j].p = pos+1;
                pos += 1;
                h++;
                break;
            }
        }

        if (found == -1) {
            int entered = -1;
            for (int j = 0; j<m; j++) {
                if (fr[j].e == 0) {
                    fr[j].c = pg[i];
                    fr[j].p = pos+1;
                    pos += 1;
                    fr[j].e = 1;
                    entered = 1;
                    break;
                }
            }

            if (entered == -1) {
                int _p = -1;
                for (int j = 0; j<m; j++) {
                    if (fr[j].p <= fr[_p].p || _p == -1) {
                        _p = j;
                    }
                }

                fr[_p].c = pg[i];
                fr[_p].p = pos+1;
                pos += 1;
            }
            mz++;

            printf("miss: ");
            for (int j = 0; j<m; j++) {
                printf("%d ", fr[j].c);
            }
            printf("\n");
        } else {
            printf("hit:  ");
            for (int j = 0; j<m; j++) {
                printf("%d ", fr[j].c);
            }
            printf("\n");
        }
    }

    printf("pos: %d, h: %d, m: %d\n", pos, h, mz);
}

