/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:57:42 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/25 13:37:31 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ft_strlen(token) - 1 == -2 quotes + 1 \0 == -1
char	*strip_quotes(char *token)
{
	char	*stripped;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(token);
	if (!ft_isinset(token[0], "\'\"") && !ft_isinset(token[len], "\'\""))
		return (token);
	stripped = ft_calloc(ft_strlen(token) - 1, sizeof(char));
	i = 1;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\"' && !token[i + 1])
			break ;
		stripped[j++] = token[i++];
	}
	free(token);
	return (stripped);
}

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

void	write_to_fd(int fd, char *line)
{
	char	**tokens;
	char	*newline;
	int		i;

	i = 0;
	tokens = NULL;
	newline = fix_line(line);
	newline = strip_quotes(newline);
	newline = expand(newline, g_envp, 0);
	newline = add_to_string(newline, '\n');
	tokens = ft_add_to_sarray(tokens, newline, 1);
	i = 0;
	while (tokens[i])
		ft_putstr_fd(tokens[i++], fd);
	ft_free_carray(tokens);
}

void	heredoc(int fd, char *delim)
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
				exit(EXIT_SUCCESS);
			write_to_fd(fd, line);
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

char	*fix_line(char *line)
{
	char	*new;
	int		i;

	new = NULL;
	new = add_to_string(new, '\"');
	i = 0;
	while (line[i])
		new = add_to_string(new, line[i++]);
	new = add_to_string(new, '\"');
	return (new);
}
