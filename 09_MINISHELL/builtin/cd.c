/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:37:30 by minkim            #+#    #+#             */
/*   Updated: 2022/07/18 14:14:33 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s2 || !s1)
		ft_error("invalid string pointers", __FILE__, __func__, __LINE__);
	while (s1[i] && s2[i])
	{
		if (s1[i] == '=' && s2[i] == '=')
			return (1);
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i])
	{
		if (s1[i] == '=')
			return (1);
		return (0);
	}
	if (s2[i])
		return (0);
	return (1);
}

char	*ft_cd_check(char *line)
{
	char	**env;

	env = g_envp;
	while (*env)
	{
		if (ft_cd_strcmp(*env, line))
			return (*env);
		env++;
	}
	return (NULL);
}

char	*ft_cd_get_val(char *home)
{
	home += 4;
	if (*home == '=')
	{
		home++;
		if (*home)
			return (home);
		else
			return ("\n");
	}
	return (NULL);
}

int	ft_cd_home_check(void)
{
	char	*home;
	char	*val;

	home = ft_cd_check("HOME");
	val = NULL;
	if (home != NULL)
		val = ft_cd_get_val(home);
	if (val != NULL)
	{
		if (*val == '\n')
			return (0);
		if (chdir(val) != 0)
			perror("Error");
	}
	if (home == NULL || val == NULL)
		printf("Error: HOME not set\n");
	return (0);
}

int	cd_exe(t_command *command)
{
	char	*home;
	char	*line;

	line = command->command;
	line += 2;
	if (*line && !ft_isspace(*line))
		return (print_and_return("Error: command not found\n"));
	if (command->arguments[1] == NULL)
		return (ft_cd_home_check());
	if (command->arguments[1][0] == '~' && !command->arguments[1][1])
	{
		home = getenv("HOME");
		if (chdir(home) != 0)
			perror("Error");
		return (0);
	}
	home = ft_cd_strdup(command->arguments[1]);
	if (chdir(home) != 0)
		perror("Error");
	free(home);
	home = NULL;
	return (0);
}
