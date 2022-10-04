/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:21:17 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/25 13:38:07 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_environment_variable(char *var, char **envp)
{
	char	*expansion;
	int		i;

	if (!var || !envp)
		return (NULL);
	expansion = NULL;
	i = -1;
	while (envp[++i])
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0 && \
								envp[i][ft_strlen(var)] == '=')
			expansion = ft_strdup(envp[i] + ft_strlen(var) + 1);
	return (expansion);
}

char	*add_to_string(char *string, char c)
{
	char	*new_string;
	int		i;

	if (!c)
		return (string);
	if (!string)
	{
		new_string = ft_calloc(2, sizeof(char));
		new_string[0] = c;
	}
	else
	{
		new_string = ft_calloc(ft_strlen(string) + 2, sizeof(char));
		i = -1;
		while (string[++i])
			new_string[i] = string[i];
		new_string[i] = c;
		free(string);
	}
	return (new_string);
}

// else if (!token[i + 1] || ft_isinset...) add a break
// after add_to_string to revert back. 
char	*get_environment_variable(char *token, int *i, char **envp)
{
	char	*variable_key;
	char	*variable_value;

	if (!token || !envp)
		return (NULL);
	variable_key = NULL;
	variable_value = NULL;
	(*i)++;
	while (token[*i])
	{
		if (ft_isinset(token[*i], "|<>$\'\"") || ft_isspace(token[*i]))
			break ;
		else if (!token[(*i) + 1] || ft_isinset(token[(*i) + 1], "|<>\'\""))
			variable_key = add_to_string(variable_key, token[(*i)++]);
		else
			variable_key = add_to_string(variable_key, token[(*i)++]);
	}
	variable_value = find_environment_variable(variable_key, envp);
	free(variable_key);
	return (variable_value);
}
