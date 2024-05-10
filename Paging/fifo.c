#include <stdio.h>

int main() {
    int i, j, n, m, found, pg[100], fr[100], k = 0, cnt = 0;
    
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    printf("Enter the page numbers:\n");
    for (i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pg[i]);
    }
    
    printf("Enter the number of frames: ");
    scanf("%d", &m);
    
    for (i = 0; i < m; i++) {
        fr[i] = -1;
    }
    
    printf("\nReference String   |   Frames   |   Status\n");
    printf("------------------------------------------\n");
    
    for (i = 0; i < n; i++) {
        found = 0;
        printf("%10d         |", pg[i]);
        
        for (j = 0; j < m; j++) {
            if (fr[j] == pg[i]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            fr[k] = pg[i];
            k = (k + 1) % m;
            cnt++; 
        }
        
        for (j = 0; j < m; j++) {
            if (fr[j] != -1) {
                printf(" %2d", fr[j]);
            } else {
                printf("  -");
            }
        }
        
        if (found) {
            printf("   |   HIT\n");
        } else {
            printf("   |   MISS\n");
        }
    }
    
    printf("------------------------------------------\n");
    printf("Total page faults: %d\n", cnt);
}


