/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:15:44 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/31 17:29:30 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_append_or_heredoc(char **tokens, t_commandtable *table, int i)
{
	if (**tokens == '>')
	{
		free(table->commands[i].outfile_path);
		table->commands[i].outfile_path = ft_strdup(tokens[1]);
		table->commands[i].mode = 1;
		table->commands[i].output = open(tokens[1], \
								O_RDWR | O_CREAT | O_APPEND, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].output);
		table->commands[i].has_redir = 1;
		return (1);
	}
	else if (**tokens == '<')
	{
		table->commands[i].input = open("heredoc", \
								O_RDWR | O_CREAT | O_TRUNC, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].input);
		heredoc(table->commands[i].input, tokens[1]);
		table->commands[i].input = open("heredoc", O_RDWR, 0777);
		table->commands[i].has_redir = 1;
		return (1);
	}
	return (0);
}

int	set_outfile_or_infile(char **tokens, t_commandtable *table, int i)
{
	if (**tokens == '>')
	{
		free(table->commands[i].outfile_path);
		table->commands[i].outfile_path = ft_strdup(tokens[1]);
		table->commands[i].mode = 0;
		table->commands[i].output = open(tokens[1], \
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].output);
		table->commands[i].has_redir = 1;
		return (1);
	}
	else if (**tokens == '<')
	{
		table->commands[i].input = open(tokens[1], O_RDONLY, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].input);
		table->commands[i].has_redir = 1;
		return (1);
	}
	return (0);
}

int	check_redirection_valid(char **tokens)
{
	int	valid;

	valid = 0;
	if (ft_strlen(*tokens) > 2 || !tokens[1])
		printf("syntax error near unexpected redirection token.\n");
	else if (tokens[0][0] == '<' && ft_strlen(tokens[0]) == 1 && \
										access(tokens[1], F_OK) < 0)
		printf("No such file or directory.\n");
	else
		valid = 1;
	return (valid);
}

int	set_redirection(char **tokens, t_commandtable *table, int i)
{
	int	valid;

	valid = 0;
	if (!tokens)
		return (valid);
	if (!check_redirection_valid(tokens))
		return (valid);
	if (ft_strlen(*tokens) <= 2)
	{
		if (ft_strlen(*tokens) == 2)
			valid = set_append_or_heredoc(tokens, table, i);
		else if (ft_strlen(*tokens) == 1)
			valid = set_outfile_or_infile(tokens, table, i);
	}
	if (table->commands[i].input == -1 || table->commands[i].output == -1)
		return (0);
	return (valid);
}
