#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<limits.h>
#define MX 200003


struct pair{
    int arrTime;
    int brustTime;
};

struct pair procArr[MX];

struct pair heap[MX];
int heapSize;

void Init() {
    heapSize = 0;
    heap[0].arrTime = -INT_MAX;
    heap[0].brustTime = -INT_MAX;
}

void Insert(struct pair element) {
    heapSize++;
    heap[heapSize] = element;
    int now = heapSize;
    while (heap[now / 2].brustTime > element.brustTime) {
        heap[now] = heap[now / 2];
        now /= 2;
    }
    heap[now] = element;
}

struct pair DeleteMin() {
    struct pair minElement, lastElement;
    int now, child;
    minElement = heap[1];
    lastElement = heap[heapSize--];
    for (now = 1; now * 2 <= heapSize; now = child) {
        child = now * 2;
        if (child != heapSize && heap[child + 1].brustTime < heap[child].brustTime) {
            child++;
        }
        if (lastElement.brustTime > heap[child].brustTime) {
            heap[now] = heap[child];
        } else
        {
            break;
        }
    }
    heap[now] = lastElement;
    return minElement;
}

int N, Q;

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

    Init();

    printf("Please enter the number of processes:\n");
    scanf("%d", &N);

    printf("Please enter the value of quantum:\n");
    scanf("%d", &Q);

    int TATarr[N];
    int WTarr[N];

    for (int i = 0; i < N; i++){
        printf("Please enter the arrival time of the %d-th process:\n", i);
        scanf("%d", &procArr[i].arrTime);
        printf("Please enter the brust time of the %d-th process:\n", i);
        scanf("%d", &procArr[i].brustTime);
    }

    start = clock();

    qsort (procArr, N, sizeof(*procArr), comp);

    int burstCopy[N];
    for (int i = 0; i < N; i++){
        burstCopy[i] = procArr[i].brustTime;
    }
    float TATavg = 0;
    float WTavg = 0;

    int cur = 0;
    int TAT;
    int WT;
    int index = 0;
    int done = 0;
    struct pair temp;
    while(done != N){
        int ok = 0;
        for (int i = 0; i < N; i++){
            if (procArr[i].arrTime <= cur && procArr[i].brustTime > 0){
                ok = 1;
                if (procArr[i].brustTime <= Q){
                    done++;
                    cur += procArr[i].brustTime;
                    TATarr[i] = cur - procArr[i].arrTime;
                    TATavg += TATarr[i];
                    WTarr[i] = TATarr[i] - burstCopy[i];
                    WTavg += WTarr[i];
                    procArr[i].brustTime = procArr[i].brustTime - Q;
                    printf("The current process's arrival time is %d and its burst time is %d\n", procArr[i].arrTime, burstCopy[i]);
                    printf("Completion Time: %d\n", cur);
                    printf("Turn-around Time: %d\n", TATarr[i]);
                    printf("Waiting Time: %d\n\n", WTarr[i]);
                }
                else{
                    procArr[i].brustTime -= Q;
                    cur += Q;
                }
            }
        }
        if (!ok){
            cur++;
        }
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