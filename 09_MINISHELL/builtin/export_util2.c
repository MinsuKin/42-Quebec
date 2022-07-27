/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:19:54 by minkim            #+#    #+#             */
/*   Updated: 2022/07/18 14:14:33 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_export_check(char *line)
{
	char	**env;

	env = g_envp;
	while (*env)
	{
		if (ft_export_strcmp(*env, line))
			return (*env);
		env++;
	}
	return (NULL);
}

int	ft_export_val_exist(char *line)
{
	while (*line)
	{
		if (*line == '=')
			return (1);
		line++;
	}
	return (0);
}

void	ft_export_val_change(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_envp[i])
	{
		if (ft_export_strcmp(g_envp[i], line))
			break ;
		i++;
	}
	tmp = g_envp[i];
	g_envp[i] = ft_strdup(line);
	free(tmp);
	tmp = NULL;
}

void	ft_export_args(char *line)
{
	char	**env;

	if (ft_isalpha(*line) || *line == '_')
	{
		if (ft_export_check(line) && ft_export_val_exist(line))
			ft_export_val_change(line);
		else
		{
			env = ft_export_add(g_envp, line);
			ft_env_free(g_envp);
			g_envp = ft_copy_env(env);
			ft_env_free(env);
		}
	}
	else
		printf("Error: not a valid identifier\n");
}

void	ft_export_insert(t_command *command)
{
	int	i;

	i = 1;
	while (command->arguments[i])
	{
		ft_export_args(command->arguments[i]);
		i++;
	}
}
