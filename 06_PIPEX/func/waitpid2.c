/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/28 16:18:21 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{ 
    pid_t pid;

    pid = fork();

    int wait_res;
    int status;
    
    if (pid == 0)
    {
        printf("\n****자식프로세스****\n");
        sleep(2);
        printf("자식프로세스 종료\n");
    }
    else
    {
        wait_res = waitpid(pid, &status, 0);
        printf("\n****부모프로세스****\n");
        sleep(1);
        printf("부모프로세스 종료\n");
        printf("wait인자값: %d\nwait반환값: %d\n", status, wait_res);
        printf("자식pid: %d\n", pid);
    }
    
}