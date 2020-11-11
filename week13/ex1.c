#include <stdio.h>

int is_less(int *a, int *b, int sz){
    for (int i = 0; i < sz; i++){
        if (a[i] > b[i]){
            return 0;
        }
    }
    return 1;
}

int min(int x, int y){
    if (x < y) return x;
    return y;
}

int main()
{
    int resNum = 3;
    int procNum = 5;

    int E[resNum], A[resNum];

    int C[procNum][resNum], R[procNum][resNum];

    freopen("C:\\Users\\prhas\\CLionProjects\\__\\input_.txt","r",stdin);

    for(int i = 0; i < resNum; i++)
        scanf("%d",&E[i]);

    for(int i = 0; i < resNum; i++)
        scanf("%d",&A[i]);

    for(int i = 0; i < procNum; i++)
        for(int j = 0; j < resNum; j++)
            scanf("%d", &C[i][j]);

    for(int i = 0; i < procNum; i++)
        for(int j = 0; j < resNum; j++)
            scanf("%d", &R[i][j]);

    int work[resNum], finish[procNum];

    for (int i = 0; i < resNum; i++)
        work[i] = A[i];
    for (int i = 0; i < procNum; i++){
        finish[i] = 1;
        for (int j = 0; j < resNum; j++){
            if (R[i][j]){
                finish[i] = 0;
                break;
            }
        }
    }

    int deadlockNum = 0;
    int deadlockedArr[procNum];
    while (1){
        int found = -1;
        for (int i = 0; i < procNum; i++){
            if (!finish[i] && is_less(R[i], work, resNum)){
                found = i;
                break;
            }
        }
        if (found == -1){
            for (int i = 0; i < procNum; i++){
                if (!finish[i]){
                    deadlockedArr[deadlockNum++] = i;
                }
            }
            break;
        }
        for (int j = 0; j < resNum; j++){
            work[j] += C[found][j];
            work[j] = min(work[j], E[j]);
        }
        finish[found] = 1;
    }

    // If there's no deadlocked processes, then there's no deadlock.
    if (!deadlockNum){
        printf("No deadlock detected!");
    } else{
        printf("Deadlock detected!\nThere are %d deadlocked processes: ", deadlockNum);
        for (int i = 0; i < deadlockNum; i++){
            printf("%d ", deadlockedArr[i] + 1);
        }
    }
    return 0;
}