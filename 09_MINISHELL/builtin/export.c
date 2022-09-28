/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:19:54 by minkim            #+#    #+#             */
/*   Updated: 2022/09/16 20:38:17 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	export_exe(t_command *command)
{
	char	**env;
	char	*line;

	line = command->command;
	line += 6;
	if (*line && !ft_isspace(*line))
		return (print_and_return("Error: command not found\n"));
	*f_exit_code() = 0;
	if (command->arguments[1] != NULL)
		ft_export_insert(command);
	else
	{
		env = ft_copy_env(g_envp);
		print_export(env);
		ft_env_free(env);
	}
	return (0);
}
