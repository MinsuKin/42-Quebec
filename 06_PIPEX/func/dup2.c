/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 12:18:49 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    int temp_fd;
    int fd[2];
    int fd2[2];
    char buffer[6];
    char buffer2[6];

    pipe(fd);
    pipe(fd2);
    temp_fd = dup2(fd[1], fd2[1]);
    printf("temp_fd: %d\nfd[1]: %d\nfd2[1]: %d\n", temp_fd, fd[1], fd2[1]);

    /* fd2[1]에 입력해보기 */
    write(fd2[1], "hello", 6);
    read(fd[0], buffer, 6);
    read(fd2[0], buffer2, 6);

    printf("\nfd[0]: %s\nfd2[0]: %s\n", buffer, buffer2);

    /* close() 생략 */
}