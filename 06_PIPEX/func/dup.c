/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 12:08:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    int fd[2];
    int fd_temp;
    char buffer[7];

    pipe(fd);
    fd_temp = dup(fd[1]);
    printf("fd[1]: %d\nfd_temp: %d\n", fd[1], fd_temp);

    /* fd_temp에 입력해보기 */
    write(fd_temp, "Hello\n", 7);
    read(fd[0], buffer, 7);
    printf("%s", buffer);

	close(fd[0]);
	close(fd[1]);
	close(fd_temp);
}