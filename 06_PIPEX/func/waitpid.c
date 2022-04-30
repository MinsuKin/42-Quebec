/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/28 16:06:05 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    pid_t pid;
    int wait_res;
    int status;

    pid = fork();

    
    if (pid == 0)
    {
        printf("\n****자식프로세스****\n");
        sleep(4);
        printf("자식프로세스 종료\n");
    }
    else
    {
        wait_res = waitpid(pid, &status, WNOHANG);
        // wait_res = waitpid(pid, 0, WNOHANG);
        printf("\n****부모프로세스****\n");
        sleep(1);
        printf("부모프로세스 종료\n");
        printf("\nwaitpid인자값: %d\nwaitpid반환값: %d\n", status, wait_res);
        // printf("\nwaitpid인자값: %d\nwaitpid반환값: %d\n", 0, wait_res);
    }

    return (0);
}