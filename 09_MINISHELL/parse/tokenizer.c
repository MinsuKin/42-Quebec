/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:26:03 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/24 14:44:25 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**tokenize(char *line)
{
	char	**tokens;
	char	*token;
	int		i;

	if (!line || !line[0])
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		token = find_token(line, &i);
		tokens = ft_add_to_sarray(tokens, token, 1);
	}
	return (tokens);
}

char	*find_token(char *line, int *i)
{
	char	*token;

	token = NULL;
	if (!line)
		return (NULL);
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (ft_isinset(line[*i], "|<>"))
		token = get_delimiter_token(line, i);
	else
		token = get_token(line, token, i);
	if (ft_strlen(token) == 0)
		return (NULL);
	return (token);
}

char	*get_unclosed_quote(char quote_type, char *token)
{
	char	*new;

	token = add_to_string(token, '\n');
	while (token[ft_strlen(token) - 1] != quote_type)
	{
		new = readline("> ");
		if (new[ft_strlen(new) - 1] != quote_type)
			new = add_to_string(new, '\n');
		token = ft_strjoin(token, new);
		free(new);
	}
	return (token);
}

char	*get_quotes_token(char *line, char *token, int *i)
{
	int		len;

	if (!line)
		return (NULL);
	token = add_to_string(token, line[(*i)]);
	len = (*i) + 1;
	while (line[len] && line[len] != line[*i])
	{
		token = add_to_string(token, line[len++]);
		if (!line[len])
			token = get_unclosed_quote(line[*i], token);
	}
	if (line[len] == line[*i])
		token = add_to_string(token, line[len++]);
	*i = len;
	return (token);
}
