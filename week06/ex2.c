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

int N;

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

    for (int i = 0; i < N; i++){
        printf("Please enter the arrival time of the %d-th process:\n", i);
        scanf("%d", &procArr[i].arrTime);
        printf("Please enter the brust time of the %d-th process:\n", i);
        scanf("%d", &procArr[i].brustTime);
    }

    start = clock();

    qsort (procArr, N, sizeof(*procArr), comp);

    float TATavg = 0;
    float WTavg = 0;

    int cur = 0;
    int TAT;
    int WT;
    int index = 0;
    int done = 0;
    struct pair temp;
    while(1){
        if (heapSize == 0){
            Insert(procArr[index]);
            index++;
        }
        temp = DeleteMin();
        done++;
        cur = max(cur, temp.arrTime);
        cur += temp.brustTime;
        TAT = cur - temp.arrTime;
        WT = TAT - temp.brustTime;
        TATavg += TAT;
        WTavg += WT;
        printf("The current process's arrival time is %d and its burst time is %d\n", temp.arrTime, temp.brustTime);
        printf("Completion Time: %d\n", cur);
        printf("Turn-arount Time: %d\n", TAT);
        printf("Waiting Time: %d\n\n", WT);
        if (done == N){
            break;
        }
        for(; index < N && procArr[index].arrTime <= cur; index++){
            Insert(procArr[index]);
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