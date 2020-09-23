#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MX 200003

int N;


struct pair{
    int arrTime;
    int brustTime;
};

struct pair procArr[MX];

int comp (const struct pair * elem1, const struct pair * elem2)
{
    int f = elem1->arrTime;
    int s = elem2->arrTime;
    if (f > s) return  1;
    if (f < s) return -1;
    f = elem1->brustTime;
    s = elem2->brustTime;
    if (f > s) return  1;
    if (f < s) return -1;
}

int max(int x, int y){
    if (x > y) return x;
    return y;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    printf("Please enter the number of processes:\n");
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        printf("Please enter the arrival time of the %d-th process:\n", i);
        scanf("%d", &procArr[i].arrTime);
        printf("Please enter the brust time of the %d-th process:\n", i);
        scanf("%d", &procArr[i].brustTime);
    }


    qsort (procArr, N, sizeof(*procArr), comp);

    float TATavg = 0;
    float WTavg = 0;

    int cur = 0;
    int TAT;
    int WT;
    for (int i = 0; i < N; i++){
        cur = max(cur, procArr[i].arrTime);
        cur += procArr[i].brustTime;
        TAT = cur - procArr[i].arrTime;
        WT = TAT - procArr[i].brustTime;
        TATavg += TAT;
        WTavg += WT;
        printf("The current process's arrival time is %d and its burst time is %d\n", procArr[i].arrTime, procArr[i].brustTime);
        printf("Completion Time: %d\n", cur);
        printf("Turn-arount Time: %d\n", TAT);
        printf("Waiting Time: %d\n\n", WT);
    }

    TATavg /= N;
    WTavg /= N;

    puts("");
    printf("Average Turn-arount Time: %f\n", TATavg);
    printf("Average Waiting Time: %f\n\n", WTavg);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken in this program is %lf", cpu_time_used);
    return 0;
}