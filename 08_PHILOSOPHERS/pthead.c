#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdatomic.h>

_Atomic int acnt = 0;

void *myThreadFun(void *vargp)
{
    (void)vargp;
    int n = 1;
    for (int j = 0; j < 3; ++j)
    {
        sleep(1);
        acnt += n;
        printf("Printing from Thread %d %llu\n", acnt, (unsigned long long)&n);
    }
    return NULL;
}

int main(void)
{
    pthread_t thread_id1, thread_id2;

    printf("Before Thread\n");

    pthread_create(&thread_id1, NULL, myThreadFun, NULL);
    pthread_create(&thread_id2, NULL, myThreadFun, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    printf("After Thread\n");
    printf("After %d\n", acnt);
    return 0;
}