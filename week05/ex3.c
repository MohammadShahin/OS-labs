#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define ALWAYS_TRUE 1
#define BUFF_MAX 100

int *buffer;
int i = 0;


pthread_mutex_t mutex_lock_var = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t bq_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t bq_not_empty = PTHREAD_COND_INITIALIZER;

void *cons();

void *prod();

int main() {
    // index_value of consumer > index_value of producer
    // consumer index == producer => consumer sleeps, producer wakes up

    pthread_t p_thread_id, c_thread_id;

    // dynamically create buffer of size BUFF_MAX
    buffer = (int *) malloc(sizeof(int) * BUFF_MAX);

    pthread_create(&p_thread_id, NULL, prod, NULL);
    pthread_create(&c_thread_id, NULL, cons, NULL);

    pthread_join(p_thread_id, NULL);
    pthread_join(c_thread_id, NULL);

    return 0;
}

void *cons() {
    while (ALWAYS_TRUE) {
        pthread_mutex_lock(&mutex_lock_var);

        if (i == -1) {
            pthread_cond_wait(&bq_not_empty, &mutex_lock_var);
        }

        printf("\nInside consumer. Id is =>:%d\n", i--);

        // unlock mutex
        // set cond signal
        pthread_mutex_unlock(&mutex_lock_var);
        pthread_cond_signal(&bq_not_full);
    }
}

void *prod() {
    while (ALWAYS_TRUE) {
        pthread_mutex_lock(&mutex_lock_var);

        if (i == BUFF_MAX) {
            pthread_cond_wait(&bq_not_full, &mutex_lock_var);
        }

        buffer[i] = 1;
        i++;

        printf("\nInside producer. Id is =>:%d\n", i);

        // same as in consumer, but not empty
        pthread_mutex_unlock(&mutex_lock_var);
        pthread_cond_signal(&bq_not_empty);
    }
}
