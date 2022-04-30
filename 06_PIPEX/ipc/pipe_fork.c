/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/27 12:44:24 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main()
{
	int pipe_fds[2];
	pid_t pid;
    char buf[1024];
    int wstatus;

    printf("[%d] start of function\n", getpid());
    memset(buf, 0, sizeof(buf));

	if (pipe(pipe_fds))
	{
		perror("pipe()");
		return -1;
	}

	pid = fork();
	if (pid == 0)
	{
		// child proc
        close(pipe_fds[1]); // 자식에서는 write을 close 하여 read만 사용가능하게

        read(pipe_fds[0], buf, sizeof(buf));
        printf("[%d] parent said... %s\n", getpid(), buf);

        close(pipe_fds[0]);
    }
	else if (pid > 0)
	{
		// parent process
        close(pipe_fds[0]); // 부모에서는 read를 close 하여 write만 사용가능하게

        strncpy(buf, "hello child!", sizeof(buf) - 1);
        write(pipe_fds[1], buf, strlen(buf));
        
        close(pipe_fds[1]);

        pid = wait(&wstatus);
	}
	else
	{
		perror("fork()");
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return -1;
	}
	return (0);
}
