/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:03:08 by tgarriss          #+#    #+#             */
/*   Updated: 2022/09/13 12:27:57 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_command(t_command *command)
{
	command->command = NULL;
	command->binary = NULL;
	command->arguments = NULL;
	command->num_args = 0;
	command->input = STDIN_FILENO;
	command->output = STDOUT_FILENO;
	command->outfile_path = NULL;
	command->mode = -1;
	command->has_redir = 0;
}

int	check_pipe_valid(char **tokens)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			if (tokens[0][0] == '|')
				valid = 0;
			if (ft_strlen(tokens[i]) > 1)
				valid = 0;
			if (tokens[i + 1])
				if (ft_isinset(tokens[i + 1][0], "|<>"))
					valid = 0;
			if (!tokens[i + 1])
				valid = 0;
		}
		i++;
	}
	if (!valid)
		ft_printf(STDERR_FILENO, "syntax error near unexpected token '|'\n");
	return (valid);
}

void	add_cmd_to_args(t_commandtable *table)
{
	int	i;

	i = 0;
	while (i < table->num_commands)
	{
		table->commands[i].arguments = ft_add_to_sarray(\
			table->commands[i].arguments, \
				ft_strdup(table->commands[i].command), 0);
		table->commands[i].num_args++;
		i++;
	}
}

int	is_var(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}
