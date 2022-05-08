/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/05/08 16:13:28 by minkim           ###   ########.fr       */
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

void	ft_child2(char **argv, char **envp, int *fd, int outfile)
{
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	ft_exe(argv[3], envp);
}

void	ft_close_n_wait(int *fd, pid_t pid, pid_t pid2)
{
	close(fd[1]);
	close(fd[0]);
	waitpid(pid, 0, 0);
	waitpid(pid2, 0, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid;
	pid_t	pid2;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY, 0644);
		outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (infile == -1 || outfile == -1)
			ft_error(1);
		if (pipe(fd) == -1)
			ft_error(1);
		pid = fork();
		if (pid == 0)
			ft_child(argv, envp, fd, infile);
		pid2 = fork();
		if (pid2 == 0)
			ft_child2(argv, envp, fd, outfile);
		ft_close_n_wait(fd, pid, pid2);
	}
	else
		ft_error(1);
	return (0);
}
