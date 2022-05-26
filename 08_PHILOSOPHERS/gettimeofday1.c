#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

size_t    relative_time(size_t time_start)
{
	struct timeval    current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - time_start);
}

int main()
{
	// struct timeval mytime;

	// gettimeofday(&mytime, NULL);
	// printf("%ld:%d\n", mytime.tv_sec, mytime.tv_usec);
	// printf("%ld:%d\n", mytime.tv_sec * 1000000, mytime.tv_usec);
	// printf("relative time is: %ld\n", mytime.tv_sec * 1000000 + mytime.tv_usec);
	// return (0);

	size_t startTime;

	// struct timeval startTime, endTime;
	// double diff_tv_sec;
	// double diff_tv_usec;

	// gettimeofday(&startTime, NULL);
	// usleep(100);
	// usleep(100);
	// gettimeofday(&endTime, NULL);
	// diff_tv_sec = ( endTime.tv_sec - startTime.tv_sec );
	// diff_tv_usec = ( endTime.tv_usec - startTime.tv_usec ) / 1000000;
	// printf("%f seconds\n", diff_tv_sec); // f는 (double로) 형변환해 출력.
	// printf("%f micro seconds\n", diff_tv_usec);

	startTime = relative_time(0);
	// printf("%zd\n", startTime);
	printf("%zd\n", relative_time(startTime));
	usleep(100);
	printf("%zd\n", relative_time(startTime));
	return 0;
}
/*
1618818045:394638
1618818045000000:394638
relative time is: 1618818045394638
*/
// 결과
// 1.000000 seconds
// 0.000000 micro seconds