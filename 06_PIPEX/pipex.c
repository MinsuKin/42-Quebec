/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/05/02 21:04:55 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child(char **argv, char **envp, int *fd, int infile)
{
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_exe(argv[2], envp);
}

void	ft_parent(char **argv, char **envp, int *fd, int outfile)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	ft_exe(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid;

	if (argc == 5)
	{
	infile = open(argv[1], O_RDONLY, 0644);
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (infile == -1 || outfile == -1)
			ft_error(1);
		if (pipe(fd) == -1)
			ft_error(1);
		pid = fork();
		if (pid == -1)
			ft_error(1);
		if (pid == 0)
			ft_child(argv, envp, fd, infile);
		else
			ft_parent(argv, envp, fd, outfile);
	}
	else
		ft_error(1);
	return (0);
}
