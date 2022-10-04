/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:15:44 by tgarriss          #+#    #+#             */
/*   Updated: 2022/09/20 10:48:47 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_heredoc(t_commandtable *table, int i, char *stripped)
{
	table->commands[i].input = open("heredoc", \
							O_RDWR | O_CREAT | O_TRUNC, 0777);
	table->open_files = ft_add_to_iarray(table->open_files, \
										table->commands[i].input);
	heredoc(table->commands[i].input, stripped);
	table->commands[i].input = open("heredoc", O_RDWR, 0777);
	table->commands[i].has_redir = 1;
	return (1);
}

int	set_append_or_heredoc(char **tokens, t_commandtable *table, int i, \
	char *stripped)
{
	if (**tokens == '>')
	{
		if (table->commands[i].outfile_path)
			free(table->commands[i].outfile_path);
		table->commands[i].outfile_path = ft_strdup(stripped);
		table->commands[i].mode = 1;
		table->commands[i].output = open(stripped, \
								O_RDWR | O_CREAT | O_APPEND, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].output);
		table->commands[i].has_redir = 1;
		return (1);
	}
	else if (**tokens == '<')
	{
		set_heredoc(table, i, stripped);
		return (1);
	}
	return (0);
}

int	set_outfile_or_infile(char **tokens, t_commandtable *table, int i, \
	char *stripped)
{
	if (**tokens == '>')
	{
		free(table->commands[i].outfile_path);
		table->commands[i].outfile_path = ft_strdup(stripped);
		table->commands[i].mode = 0;
		table->commands[i].output = open(stripped, \
								O_WRONLY | O_CREAT | O_TRUNC, 0644);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].output);
		table->commands[i].has_redir = 1;
		return (1);
	}
	else if (**tokens == '<')
	{
		table->commands[i].input = open(stripped, O_RDONLY, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].input);
		table->commands[i].has_redir = 1;
		return (1);
	}
	return (0);
}

int	check_redirection_valid(char **tokens, char *stripped)
{
	int	valid;

	valid = 0;
	if (ft_strlen(*tokens) > 2 || !stripped)
		ft_printf(STDERR_FILENO, \
			"syntax error near unexpected redirection token.\n");
	else if (ft_isinset(stripped[0], "<>|"))
		ft_printf(STDERR_FILENO, \
			"syntax error near unexpected redirection token.\n");
	else if (tokens[0][0] == '<' && ft_strlen(tokens[0]) == 1 && \
										access(stripped, F_OK) < 0)
		ft_printf(STDERR_FILENO, "No such file or directory.\n");
	else if (!tokens[1])
		ft_printf(STDERR_FILENO, "syntax error near unexpected \'\\n\' token\n");
	else
		valid = 1;
	if (!valid)
		free(stripped);
	return (valid);
}

int	set_redirection(char **tokens, t_commandtable *table, int i)
{
	char	*stripped;
	int		valid;

	valid = 0;
	if (!tokens)
		return (valid);
	stripped = strip_quotes(ft_strdup(tokens[1]));
	if (!check_redirection_valid(tokens, stripped))
		return (valid);
	if (ft_strlen(*tokens) <= 2)
	{
		if (ft_strlen(*tokens) == 2)
			valid = set_append_or_heredoc(tokens, table, i, stripped);
		else if (ft_strlen(*tokens) == 1)
			valid = set_outfile_or_infile(tokens, table, i, stripped);
	}
	if (table->commands[i].input == -1 || table->commands[i].output == -1)
	{
		ft_printf(STDERR_FILENO, \
			"cannot open: %s: permission denied\n", tokens[1]);
		return (0);
	}
	free(stripped);
	return (valid);
}
