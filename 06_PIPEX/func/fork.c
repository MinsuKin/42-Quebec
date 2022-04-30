/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/27 11:40:56 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    pid_t pid;
 
    pid = fork();

    if (pid == -1)
    {
        printf("fork() error");
        exit(1);
    }
    printf("pid = %d\n", pid);
    if (pid == 0)
    {
        printf("\n****child****\n");
        printf("변수pid값: %d\n", pid);
        printf("자식피드: %d\n", getpid());
    }
    else
    {
        printf("\n****parent****\n");
        printf("변수pid값: %d\n", pid);
        printf("부모피드: %d\n", getpid());
    }
    return (0);
}