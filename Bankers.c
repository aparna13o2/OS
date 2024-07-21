#include<stdio.h>

int available[10];
int need[10][10], max[10][10], allocation[10][10], work[10];
int m, n;
int i, j, k;

void readMat(int mat[10][10]) {
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void displayMat(int mat[10][10]) {
    for(i = 0; i < n; i++) {
        printf("P %d  ", i);
        for(j = 0; j < m; j++) {
            printf("%d   ", mat[i][j]);
        }
        printf("\n");
    }
}

void calc_need() {
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void banker() {
    int flag;
    int finish[10] = {0};  // initialize finish array
    int safeseq[10];
    int work_temp[10];
    
    for(i = 0; i < m; i++) {
        work_temp[i] = available[i];
    }

    k = 0;
    while(k < n) {
        flag = 0;
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int can_allocate = 1;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work_temp[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if(can_allocate) {
                    finish[i] = 1;
                    safeseq[k++] = i;
                    for(j = 0; j < m; j++) {
                        work_temp[j] += allocation[i][j];
                    }
                    flag = 1;
                }
            }
        }
        if(flag == 0) {
            printf("deadlock\n");
            return;
        }
    }
    
    printf("Safe sequence: ");
    for(i = 0; i < n; i++) {
        printf("P%d ", safeseq[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);
    
    printf("Enter the allocation table:\n");
    readMat(allocation);
    
    printf("Enter the max table:\n");
    readMat(max);
    
    printf("Enter the available resources for each resource type:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    calc_need();
    
    printf("\nMAX TABLE\n");
    displayMat(max);
    
    printf("\nALLOCATION TABLE\n");
    displayMat(allocation);
    
    printf("\nNEED TABLE\n");
    displayMat(need);
    
    printf("\nAvailable resources: ");
    for(i = 0; i < m; i++) {
        printf("%d   ", available[i]);
    }
    printf("\n");
    
    banker();
    
    return 0;
}
