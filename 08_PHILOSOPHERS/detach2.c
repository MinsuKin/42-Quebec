#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *t_function(void *param)
{
    for (int i = 1; i <= 5; i++)
    {
        usleep(1000); 
        // 여기서 main쓰레드로 넘어감.
        // main에서는 그 다음 명령이 detach이므로
        // 그 시점에 바로 쓰레드 종료.
        printf("쓰레드 함수 실행 중..%d/5\n",i);
    }
        printf("쓰레드 함수 종료\n");
        return (void *)2147483647;
}

int main()
{
    pthread_t p_thread;
    int thr_id;
    // int result;

    thr_id = pthread_create(&p_thread, NULL, t_function, NULL);
    if (thr_id < 0)
    {
        perror("thread create error : ");
        exit(0);
    } 
    pthread_detach(p_thread);

    printf("main() 종료\n");

    return 0;
}
