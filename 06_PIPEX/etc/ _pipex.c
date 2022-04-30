/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/30 16:58:09 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_error(int exit_failure)
{
	perror("Error");
	exit(exit_failure);
}

static char *ft_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

static char *ft_cmd(char *cmd, char **envp)
{
	char	**path;
	char	*input;
	int		i;

	path = ft_split(ft_path(envp)+5, ':');
	if (path == 0)
		ft_error(0);
	
	i = 0;
	while (path[i])
	{
		input = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		
		if (access(input, X_OK) == 0)
			return input;
		i++;
	}
	return (NULL);
}

void ft_exe(char *argv, char **envp)
{
	char *cmd;
	char **option;

	option = ft_split(argv, ' ');
	cmd = ft_cmd(option[0], envp);
	if (option == 0)
		ft_error(0);
	if (execve(cmd, option, envp) == -1)
		ft_error(0);
}

void ft_child(char **argv, char **envp, int *fd, int infile)
{
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_exe(argv[2], envp);
}

void ft_parent(char **argv,char **envp, int *fd, int outfile)
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

	infile = open(argv[1], O_RDONLY, 0644);
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (infile == -1 || outfile == -1)
		ft_error(0);
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			ft_error(0);
		pid = fork();
		if (pid == -1)
			ft_error(0);
		if (pid == 0)
			ft_child(argv, envp, fd, infile);
		waitpid(pid, 0, WNOHANG);
		ft_parent(argv, envp, fd, outfile);
	}

	//printf("%s\n", envp[i] + 5);

}
