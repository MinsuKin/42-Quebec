/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/19 21:58:52 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    int fd1[2];
    int fd2[2];
    char buffer[4096];
    pid_t pid;

    if(pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        printf("pipe error");
        exit(1);
    }

    pid = fork();

    if (pid == -1)
    {
        printf("fork() error");
        exit(1);
    }
    if (pid == 0)
    {
        write(fd1[1], "(자식에서 입력)\n", 25);
        read(fd2[0], buffer, 25);
        printf("\n자식출력: %s\n", buffer);

    }
    else
    {
        // write(fd2[1], "(부모에서 입력)", 25);
        read(fd1[0], buffer, 4096);
        printf("\n부모출력: %s\n", buffer);
    }

    // if (pid == 0)
    // {
    //     write(fd1[1], "(자식에서 입력)\n", 25);
    //     read(fd2[0], buffer, 25);
    //     printf("\n자식출력: %s\n", buffer);

    // }
    // else
    // {
    //     wait(NULL);  // wait함수 추가
    //     write(fd2[1], "(부모에서 입력)", 25);
    //     read(fd1[0], buffer, 4096);
    //     printf("\n부모출력: %s\n", buffer);
    // }
    // return (0);
}
