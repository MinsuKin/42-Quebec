/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:09:48 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/25 13:56:26 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_token(char *line, char *token, int *i)
{
	if (!line || !line[*i])
		return (NULL);
	while (line[*i] && !ft_isinset(line[*i], "<>|"))
	{
		if (ft_isinset(line[*i], "\'\""))
			token = get_quotes_token(line, token, i);
		else if (ft_isspace(line[*i]))
			break ;
		else
			token = get_alpha_token(line, token, i);
	}
	return (token);
}

char	*get_alpha_token(char *line, char *token, int *i)
{
	if (!line)
		return (NULL);
	while (line[*i] && !ft_isinset(line[*i], "<>|\'\""))
	{
		if (ft_isspace(line[*i]))
			break ;
		token = add_to_string(token, line[(*i)++]);
	}
	return (token);
}

char	*get_delimiter_token(char *line, int *i)
{
	char	*token;
	int		len;

	if (!line)
		return (NULL);
	len = (*i) + 1;
	while (line[len] && line[len] == line[*i])
		len++;
	token = ft_substr(line, *i, (len - *i));
	*i = len;
	return (token);
}
