#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int	main(void)
{
	const char		*wday[] = {"일", "월", "화", "수", "목", "금", "토"};
	struct timeval	unix;
	struct tm		*date;

	if (gettimeofday(&unix, NULL) == -1)
		return (1);
	printf("Unix Time: %ld\t%d\n", unix.tv_sec, unix.tv_usec);
	date = localtime(&(unix.tv_sec));
	if (!date)
		return (1);
	printf("Date Time: %d년 %d월 %d일 %s요일 %02d시 %02d분 %02d초 %s\n",
		   date->tm_year + 1900,
		   date->tm_mon + 1,
		   date->tm_mday,
		   wday[date->tm_wday],
		   date->tm_hour,
		   date->tm_min,
		   date->tm_sec,
		   date->tm_zone);
	printf("%d days passed from Jan 1st\n", date->tm_yday);
	return (0);
}