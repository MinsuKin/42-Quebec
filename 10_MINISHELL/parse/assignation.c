/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:01:33 by tgarriss          #+#    #+#             */
/*   Updated: 2022/09/11 18:59:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	assign_token(char **tokens, t_commandtable *table, int index)
{
	char	*token;

	if (!tokens)
		return (0);
	token = ft_strdup(*tokens);
	if (table->commands[index].command == NULL)
		table->commands[index].command = ft_strdup(token);
	else
	{
		table->commands[index].arguments = ft_add_to_sarray(\
			table->commands[index].arguments, ft_strdup(token), 1);
		table->commands[index].num_args = ft_get_array_length(\
			table->commands[index].arguments);
	}
	free(token);
	return (1);
}

int	set_tokens(char **tokens, t_commandtable *table)
{
	int	i;
	int	j;

	if (!tokens || ! table)
		return (0);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
			j++;
		else if (tokens[i][0] == '>' || tokens[i][0] == '<')
		{
			if (!set_redirection(&tokens[i++], table, j))
				return (0);
		}
		else
		{
			if (!assign_token(&tokens[i], table, j))
				return (0);
		}
		i++;
	}
	return (1);
}

void	set_pipe(t_commandtable *table, int i)
{
	if (pipe(table->commands[i].pipe) == -1)
		ft_error("pipe() failed", __FILE__, __func__, __LINE__);
	if (i == 0 && table->num_commands > 1)
	{
		table->commands[i].input = STDIN_FILENO;
		table->commands[i].output = table->commands[i].pipe[WRITE_END];
	}
	else if (i == 0 && table->num_commands == 1)
	{
		table->commands[i].input = STDIN_FILENO;
		table->commands[i].output = STDOUT_FILENO;
	}
	else if (i > 0 && i < table->num_commands - 1)
	{
		table->commands[i].input = table->commands[i - 1].pipe[READ_END];
		table->commands[i].output = table->commands[i].pipe[WRITE_END];
	}
	else
	{
		table->commands[i].input = table->commands[i - 1].pipe[READ_END];
		table->commands[i].output = STDOUT_FILENO;
	}
}

void	set_pipes(t_commandtable *table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	if (pipe(table->pipe_fd) == -1)
		ft_error("pipe() failed.", __FILE__, __func__, __LINE__);
	while (i < table->num_commands)
	{
		table->commands[i].table = table;
		init_command(&table->commands[i++]);
	}
	i = -1;
	while (++i < table->num_commands)
		set_pipe(table, i);
}

t_commandtable	*set_commandtable(char **tokens)
{
	t_commandtable	*table;

	if (!tokens)
		return (NULL);
	if (!check_pipe_valid(tokens))
		return (NULL);
	table = ft_calloc(1, sizeof(t_commandtable));
	if (!table)
		ft_error("Table creation failed.", __FILE__, __func__, __LINE__);
	table->num_commands = get_num_commands(tokens);
	table->commands = ft_calloc(table->num_commands, sizeof(t_command));
	table->open_files = NULL;
	table->pid = 0;
	set_pipes(table);
	if (!set_tokens(tokens, table))
	{
		free_commandtable(table);
		return (NULL);
	}
	add_cmd_to_args(table);
	return (table);
}
