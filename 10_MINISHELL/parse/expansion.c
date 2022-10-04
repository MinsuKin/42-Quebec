/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:27:49 by tgarriss          #+#    #+#             */
/*   Updated: 2022/09/13 12:36:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variable(char *token, char *expanded, int *i, char **envp)
{
	char	*new;
	char	*variable;

	new = ft_strdup(expanded);
	variable = NULL;
	while (token[*i] && !ft_isinset(token[*i], "\'\""))
	{
		if (token[*i] == '$' && token[(*i) + 1] == '?')
		{
			*i += 2;
			variable = ft_itoa(*f_exit_code());
			new = ft_strjoin(new, variable);
			free(variable);
		}
		else if (token[*i] == '$' && is_var(token[(*i) + 1]))
		{
			variable = get_environment_variable(token, i, envp);
			new = ft_strjoin(new, variable);
			free(variable);
		}
		else
			new = add_to_string(new, token[(*i)++]);
	}
	free(expanded);
	return (new);
}

char	*expand_double_quotes(char *token, int *i, char *expanded, char **envp)
{
	char	*new;

	new = ft_strdup(expanded);
	new = add_to_string(new, token[(*i)++]);
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
			new = expand_variable(token, new, i, envp);
		else
		{
			if (token[*i])
				new = add_to_string(new, token[(*i)++]);
			while (token[*i] && !ft_isinset(token[*i], "|<>$\'\""))
				new = add_to_string(new, token[(*i)++]);
		}
	}
	if (token[*i] == '\"')
		new = add_to_string(new, token[(*i)++]);
	while (token[*i] && !ft_isinset(token[*i], "|<>$\'\""))
		new = add_to_string(new, token[(*i)++]);
	free(expanded);
	return (new);
}

char	*expand_single_quotes(char *token, int *i, char *expanded)
{
	char	*new;

	new = ft_strdup(expanded);
	new = add_to_string(new, token[(*i)++]);
	while (token[*i] && token[*i] != '\'')
		new = add_to_string(new, token[(*i)++]);
	if (token[*i] && token[*i] == '\'')
		new = add_to_string(new, token[(*i)++]);
	while (token[*i] && !ft_isinset(token[*i], "|<>$\'\""))
		new = add_to_string(new, token[(*i)++]);
	free(expanded);
	return (new);
}

char	*remove_quotes(char *token, int i)
{
	char	*new;
	int		in_quotes;
	char	type;

	if (!token)
		return (token);
	new = NULL;
	in_quotes = 0;
	while (token[i])
	{
		if (token[i] && ft_isinset(token[i], "\'\"") && !in_quotes)
		{
			type = token[i++];
			in_quotes = 1;
			while (token[i] && token[i] != type)
				new = add_to_string(new, token[i++]);
			if (token[i])
				i++;
			in_quotes = 0;
		}
		else if (token[i])
			new = add_to_string(new, token[i++]);
	}
	free(token);
	return (new);
}

char	*expand(char *token, char **envp, int remove)
{
	char	*expanded;
	int		i;

	if (!token || !envp)
		return (NULL);
	expanded = NULL;
	i = 0;
	while (token[i])
	{
		if ((token[i] && token[i] == '\"') || (token[i] == '\'' && !remove))
			expanded = expand_double_quotes(token, &i, expanded, envp);
		else if (token[i] && token[i] == '\'')
			expanded = expand_single_quotes(token, &i, expanded);
		else if (token[i] && token[i] == '$')
			expanded = expand_variable(token, expanded, &i, envp);
		else if (token[i])
			expanded = add_to_string(expanded, token[i++]);
		else
			ft_printf(STDERR_FILENO, "SOMETHING MIGHT'VE FUCKED UP\n");
	}
	free(token);
	if (remove)
		expanded = remove_quotes(expanded, 0);
	return (expanded);
}
