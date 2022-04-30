/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/22 16:52:57 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid;

	infile = open(argv[1], O_RDONLY, 0777);
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (infile == -1 || outfile == -1)
		error();
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_proc(argv, envp, fd, infile);
		waitpid(pid, 0, 0);
		parent_proc(argv, envp, fd, outfile);
	}
	return (0);
}
