/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_from_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:43:16 by minkim            #+#    #+#             */
/*   Updated: 2022/07/21 15:10:53 by minkim           ###   ########.fr       */
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

static char	*bin_path(char **g_envp)
{
	int	i;

	i = 0;
	while (g_envp[i])
	{
		if (ft_strncmp("PATH=", g_envp[i], 5) == 0)
			return (g_envp[i]);
		i++;
	}
	return (0);
}

static char	*bin_cmd(char *cmd, char **g_envp)
{
	char	**path;
	char	*input;
	char	*tmp;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	tmp = bin_path(g_envp);
	if (tmp == 0)
		return (0);
	path = bin_split(tmp + 5, ':');
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

void	bin_exe(t_command *command, char **g_envp)
{
	char	*cmd;
	char	**option;

	if (command->command == NULL)
	{
		ft_env_free(command->arguments);
		exit(1);
	}
	option = command->arguments;
	cmd = bin_cmd(command->command, g_envp);
	if (cmd == 0 || execve(cmd, option, g_envp) == -1)
	{
		ft_env_free(option);
		printf("Error: command not found\n");
		exit(1);
	}
}
