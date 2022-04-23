/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 20:01:16 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int argc, char **argv)
{
    int i;
    if (argc > 0)
        i = 0;
    
    char *envp[] = {0};

    execve("/bin/mv", argv, envp);
    return (0);
}