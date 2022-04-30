
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    int pid;
    int status;
    int spid;
    pid = fork();

    if (pid == 0)
    {
        sleep(5);
        printf("I will be back %d\n", getpid());
        // exit(EXIT_FAILURE);
        return 1;
    }

    else if(pid > 0)
    {
        printf("Im parent %d\n", getpid());
        printf("Press any key and wait\n");
        getchar();
        // 자식프로세스를 wait 한다.
        // 자식프로세스의 종료상태는 status 를 통해 받아온다.
        spid = wait(&status);
        printf("자식프로세스 wait 성공 \n");
        // 자식프로세스의 PID, 리턴값, 종료상태(정상종료혹은 비정상종료)를
        // 얻어온다.
        printf("PID         : %d\n", spid);
        printf("Exit Value  : %d\n", WEXITSTATUS(status));
        printf("Exit Stat   : %d\n", WIFEXITED(status));
    }
    else
    {
        perror("fork error :");
    }
}
		