/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:19:54 by minkim            #+#    #+#             */
/*   Updated: 2022/07/18 14:14:33 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_exe(t_command *command)
{
	char	**env;
	char	*line;

	line = command->command;
	line += 6;
	if (*line && !ft_isspace(*line))
		return (print_and_return("Error: command not found\n"));
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
