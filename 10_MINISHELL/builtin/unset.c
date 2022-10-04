/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:13:31 by minkim            #+#    #+#             */
/*   Updated: 2022/09/06 11:33:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_strcmp(const char *s1, const char *s2)
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

int	ft_unset_check(char *line)
{
	int	i;

	i = 0;
	while (g_envp[i])
	{
		if (ft_unset_strcmp(g_envp[i], line))
			return (i);
		i++;
	}
	return (0);
}

void	ft_unset(char *line)
{
	int		i;
	char	*tmp;

	i = ft_unset_check(line);
	if (i != 0)
	{
		while (g_envp[i + 1])
		{
			tmp = g_envp[i];
			g_envp[i] = g_envp[i + 1];
			g_envp[i + 1] = tmp;
			i++;
		}
		free(g_envp[i]);
		g_envp[i] = NULL;
	}
}

int	unset_exe(t_command *command)
{
	char	*line;
	char	*arg;
	int		i;

	line = command->command;
	line += 5;
	if (*line && !ft_isspace(*line))
		return (print_and_return("Error: command not found\n"));
	if (command->arguments[1] == NULL)
		return (0);
	i = 1;
	*f_exit_code() = 0;
	while (command->arguments[i])
	{
		arg = command->arguments[i];
		if (ft_isalpha(*arg) || *arg == '_')
			ft_unset(arg);
		else
			print_and_return3("Error: not a valid identifier\n");
		i++;
	}
	return (0);
}
