/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:28:49 by minkim            #+#    #+#             */
/*   Updated: 2022/05/02 17:00:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int exit_code)
{
	perror("Error");
	exit(exit_code);
}

static char	*ft_path(char **envp)
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

static char	*ft_cmd(char *cmd, char **envp)
{
	char	**path;
	char	*input;
	int		i;

	path = ft_split(ft_path(envp)+5, ':');
	if (path == 0)
		ft_error(1);
	i = 0;
	while (path[i])
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		input = ft_strjoin(ft_strjoin(path[i], "/"), cmd);
		if (access(input, X_OK) == 0)
			return (input);
		i++;
	}
	ft_error(1);
	return (NULL);
}

void	ft_exe(char *argv, char **envp)
{
	char	*cmd;
	char	**option;

	option = ft_split(argv, ' ');
	cmd = ft_cmd(option[0], envp);
	if (option == 0)
		ft_error(1);
	if (execve(cmd, option, envp) == -1)
		ft_error(1);
}
