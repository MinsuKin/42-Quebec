/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:15:44 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/21 16:58:47 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_child(void);
void    setting_signal();

// this seems to work but wtf?
int	mini_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (s1[i] && s2[i] && i < n && i < ft_strlen(s1))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// check ft_error to make sure it works ok
// heredoc signals (minsu)
void	write_to_fd(int fd, char *delim)
{
	char	*line;
	int		pid;

	pid = fork();
	signal(SIGINT, SIG_DFL);
	if (pid == 0)
	{
		line = readline("> ");
		while (mini_strncmp(line, delim, ft_strlen(delim)) != 0)
		{
			if (!line)
				exit(EXIT_SUCCESS); // ctrl + D
			line = add_to_string(line, '\n');
			ft_putstr_fd(line, fd);
			free(line);
			line = readline("> ");
		}
		free(line);
		exit(EXIT_SUCCESS);
	}
	signal(SIGINT, sig_handler_heredoc);
	wait_child();
	close(fd);
}

int	set_append_or_heredoc(char **tokens, t_commandtable *table, int i)
{
	if (**tokens == '>')
	{
		table->commands[i].output = open(tokens[1], O_CREAT | O_APPEND, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].output);
		return (1);
	}
	else if (**tokens == '<')
	{
		table->commands[i].input = open("heredoc", O_TRUNC | O_CREAT | O_RDWR, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].input);
		write_to_fd(table->commands[i].input, tokens[1]);
		open("heredoc", O_CREAT | O_RDWR, 0777);
	}
	return (0);
}

int	set_outfile_or_infile(char **tokens, t_commandtable *table, int i)
{
	if (**tokens == '>')
	{
		table->commands[i].output = open(tokens[1], O_RDWR | O_CREAT, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].output);
		return (1);
	}
	else if (**tokens == '<')
	{
		table->commands[i].input = open(tokens[1], O_RDONLY, 0777);
		table->open_files = ft_add_to_iarray(table->open_files, \
											table->commands[i].input);
		return (1);
	}
	return (0);
}

int	set_redirection(char **tokens, t_commandtable *table, int i)
{
	if (!tokens)
		return (0);
	if (!tokens[1] || tokens[1][0] == '|')
		return (0);
	if (ft_strlen(*tokens) == 2)
	{
		set_append_or_heredoc(tokens, table, i);
	}
	else if (ft_strlen(*tokens) == 1)
	{
		set_outfile_or_infile(tokens, table, i);
	}
	else
		ft_error("syntax error near unexpected token '<' or '>'", __FILE__, __func__, __LINE__);
	// what does this do?
	if (table->commands[i].input == -1 || table->commands[i].output == -1)
		return (0);
	return (1);
}
