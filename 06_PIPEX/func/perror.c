/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 17:02:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    int fd[2];
    char buffer[30];

    pipe(fd);
    dup2(fd[1], 2);
    perror("ERROR!");
    read(fd[0], buffer, 30);
    printf("%s", buffer);

    // int fd[2];

    // pipe(fd);
    // dup2(fd[1], 2);
    // perror("ERROR!");

    /* close() 생략 */
}