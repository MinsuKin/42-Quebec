/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:01:33 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/18 22:22:13 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "time.h"

// char	**add_to_unclosed_pipe(char **tokens)
// {
// 	char	**add_tokens;
// 	char	*new_line;
// 	char	*line;
// 	int		i;

// 	i = -1;
// 	add_tokens = NULL;
// 	line = NULL;
// 	while (tokens[++i])
// 	{
// 		if (tokens[i][0] == '|' && ft_strlen(tokens[i]) > 1)
// 			ft_error("unexpected parse error near |", __FILE__, __func__, __LINE__);
// 		else if (tokens[i][0] == '|' && !tokens[i + 1])
// 		{
// 			continue ;
// 			line = readline("pipe> ");
// 			if (!line)
// 				control_d();
// 			else if (*line == '\0')
// 				free(line);
// 			else
// 			{
// 				new_line = reformat_string(line);
// 				add_tokens = tokenize(new_line);
// 				free(new_line);
// 			}
// 		}
// 		else if (tokens[i][0] == '|' && (tokens[i + 1][0] == '|' || tokens[i][1] == '|'))
// 		{
// 			ft_error("unexpected parse error near |", __FILE__, __func__, __LINE__);
// 			// change this
// 		}
// 	}
// 	if (!add_tokens)
// 		return (tokens);
// 	i = -1;
// 	while (add_tokens[++i])
// 		tokens = add_to_array(tokens, add_tokens[i]);
// 	free(add_tokens);
// 	return (tokens);
// }

void	init_command(t_command *command)
{
	command->command = NULL;
	command->binary = NULL;
	command->options = NULL;
	command->arguments = NULL;
	command->num_args = 0;
	command->input = STDIN_FILENO;
	command->output = STDOUT_FILENO;

}

int	unclosed_pipe_loop(char **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
		i++;
	if (tokens[i - 1][0] == '|')
		return (1);
	return (0);
}

char	*expand_new(char *token, char **g_envp);

int	assign_token(char **tokens, t_commandtable *table, int index)
{
	char	*new_token;
	char	*token;
	
	if (!tokens)
		return (0);
	token = ft_strdup(*tokens);
	new_token = expand_new(token, g_envp);
	free(token);
	if (!new_token)
		return (0);
	if (table->commands[index].command == NULL)
		table->commands[index].command = ft_strdup(new_token);
	else
	{
		table->commands[index].arguments = ft_add_to_sarray(table->commands[index].arguments, ft_strdup(new_token), 1);
		table->commands[index].num_args = ft_get_array_length(table->commands[index].arguments);
	}
	free(new_token);
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
			if (set_redirection(&tokens[i], table, j))
			{
				i++;
			}
		}
		else
		{
			assign_token(&tokens[i], table, j);
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
	// fix this so it exits properly.
	if (pipe(table->pipe_fd) == -1)
		ft_error("pipe() failed.", __FILE__, __func__, __LINE__);
	while (i < table->num_commands)
	{
		table->commands[i].table = table;
		init_command(&table->commands[i]);
		i++;
	}
	i = -1;
	while (++i < table->num_commands)
		set_pipe(table, i);
}

void	print_command_table(t_commandtable *table)
{
	int	i;
	int	j;

	if (!table)
		return ;
	i = 0;
	while (i < table->num_commands)
	{
		printf("--- %d ---\n", i);
		printf("Command: %s\n", table->commands[i].command);
		printf("pipeIN: %d, pipeOUT: %d\n", table->commands[i].pipe[READ_END], table->commands[i].pipe[WRITE_END]);
		j = 0;
		printf("Args: ");
		while (j < table->commands[i].num_args)
		{
			printf("%s, ", table->commands[i].arguments[j]);
			j++;
		}
		printf("\n");
		printf("Input: %d Output: %d\n", table->commands[i].input, table->commands[i].output);
		i++;
	}
	if (table->open_files)
	{
		i = 0;
		printf("open files: ");
		while (i < table->open_files->size)
		{
			printf("%d, ", table->open_files->array[i]);
			i++;
		}
		printf("\n");
	}
}

void	check_pipe_error(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|')
		{
			if (ft_strlen(tokens[i]) > 1)
				ft_error("unexpected parse error near |", __FILE__, __func__, __LINE__);
			if (tokens[i + 1])
			{
				if (tokens[i + 1][0] == '|')
					ft_error("unexpected parse error near |", __FILE__, __func__, __LINE__);
			}
			if (!tokens[i + 1])
				ft_error("unexpected parse error near |", __FILE__, __func__, __LINE__);
		}
		i++;
	}
}

void	add_cmd_to_args(t_commandtable *table)
{
	int	i;

	i = 0;
	while (i < table->num_commands)
	{
		table->commands[i].arguments = ft_add_to_sarray(table->commands[i].arguments, ft_strdup(table->commands[i].command), 0);
		table->commands[i].num_args++;
		i++;
	}
}

t_commandtable	*set_commandtable(char **tokens)
{
	t_commandtable	*table;

	if (!tokens)
		return (NULL);
	table = ft_calloc(1, sizeof(t_commandtable));
	if (!table)
		ft_error("Table creation failed.", __FILE__, __func__, __LINE__);
	// while (unclosed_pipe_loop(tokens))
	// 	tokens = add_to_unclosed_pipe(tokens);
	check_pipe_error(tokens);
	table->num_commands = get_num_commands(tokens);
	table->commands = ft_calloc(table->num_commands, sizeof(t_command));
	table->open_files = NULL;
	set_pipes(table);
	if (!set_tokens(tokens, table))
		ft_error("token assignation failed.", __FILE__, __func__, __LINE__);
	add_cmd_to_args(table);
	return (table);
}
