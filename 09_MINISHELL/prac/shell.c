#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAXLINE 64

int main(int argc, char **argv)
{
	char buf[MAXLINE];
	int proc_status;
	pid_t pid;

	printf("Shell v 1.0\n");
	while (1)
	{
		memset(buf, 0x00, MAXLINE);
		fgets(buf, MAXLINE - 1, stdin);
		if (strncmp(buf, "exit\n", 5) == 0) {
			break;
		}
		buf[strlen(buf)-1] = 0x00;

		pid = fork();
		if (pid == 0)
		{
			if (execl(buf, buf, NULL) == -1)
			{
				printf("command execution is failed\n");
				exit(0);
			}
		}
		if (pid > 0)
		{
			wait(NULL);
		}
	}
	return 0;
}