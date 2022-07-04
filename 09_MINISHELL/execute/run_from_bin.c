/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_from_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:43:16 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*bin_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	bytes;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	bytes = (ft_strlen(s1) + ft_strlen(s2) + 1);
	newstr = malloc(sizeof(char) * bytes);
	if (!newstr)
		return (0);
	while (s1 != NULL && s1[j])
		newstr[i++] = s1[j++];
	j = 0;
	while (s2 != NULL && s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free((void *)s1);
	s1 = NULL;
	return (newstr);
}

static char	*bin_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i]);
		i++;
	}
	return (0);
}

static char	*bin_cmd(char *cmd, char **envp)
{
	char	**path;
	char	*input;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = bin_split(bin_path(envp)+5, ':');
	i = 0;
	while (path[i])
	{
		input = bin_strjoin(bin_strjoin(path[i], "/"), cmd);
		if (access(input, X_OK) == 0)
		{
			free(path);
			return (input);
		}
		i++;
		free(input);
	}
	free(path);
	return (0);
}

void	bin_exe(char *argv, char **envp)
{
	char	*cmd;
	char	**option;

	option = bin_split(argv, ' ');
	cmd = bin_cmd(option[0], envp);
	if (cmd == 0 || execve(cmd, option, envp) == -1)
	{
		ft_env_free(option);
		perror("Error");
		exit(1);
	}
}
