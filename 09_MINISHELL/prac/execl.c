#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int pid;
	int child_pid;
	// int status;

	pid = fork();
	switch (pid)
	{
		case -1:
			perror("fork is failed\n");
			break;
		
		case 0:
			execl("/bin/ls", "ls", "-al", NULL);
			perror("execl is failed\n");
			break;
		
		default:
				child_pid = wait(NULL);
				printf("ls is complete\n");
				printf("Parent PID (%d), Child PID (%d) \n", getpid(), child_pid);
				exit(0);
	}
}