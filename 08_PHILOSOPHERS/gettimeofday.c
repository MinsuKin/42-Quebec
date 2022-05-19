#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    struct timeval startTime, endTime;
    double diff_tv_sec;
    double diff_tv_usec;

    gettimeofday(&startTime, NULL);
    usleep(1000 * 1000);
    gettimeofday(&endTime, NULL);
    diff_tv_sec = ( endTime.tv_sec - startTime.tv_sec );
    diff_tv_usec = ( endTime.tv_usec - startTime.tv_usec ) / 1000000;
    printf("%f seconds\n", diff_tv_sec); // f는 (double로) 형변환해 출력.
    printf("%f micro seconds\n", diff_tv_usec);
    return 0;
}

// 결과
// 1.000000 seconds
// 0.000000 micro seconds