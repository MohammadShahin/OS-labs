#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void *myThreadFun(void *vargp)
{
    printf("This message is from thread number %d %d\n", (int) pthread_self(), (int) vargp);
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    int N = 3;
    int status;
    int i;
    pthread_t tid[N];
    for (i = 1; i <= N; i++) {
        status = pthread_create(&tid[i - 1], NULL, myThreadFun, (void *) i);
        if (status){
            printf("Thread %d %d was NOT created successfully!\n", (int) tid[i - 1], i);
            exit(1);
        }
        printf("Thread %d %d created successfully!\n", (int) tid[i - 1], i);
       	status = pthread_join(tid[i - 1], NULL);
       	if (status){
       		printf("Thread %d %d did NOT end successfully!\n", (int) tid[i - 1], i);
            exit(1);
       	}
       	printf("Thread %d %d ended successfully!\n", (int) tid[i - 1], i);
    }
    pthread_exit(NULL);
    return 0;
}

