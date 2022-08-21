/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:21:17 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/18 22:01:51 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_environment_variable(char *var, char **g_envp)
{
	char	*expansion;
	int		start;
	int		i;

	if (!var || !g_envp)
		return (NULL);
	i = -1;
	expansion = NULL;
	if (ft_strncmp(var, "$?", 2) == 0)
	{
		expansion = ft_itoa(*f_exit_code());
		free(var);
		return (expansion);
	}
	while (g_envp[++i])
	{
		start = 0;
		if (ft_strncmp(g_envp[i], &var[start], ft_strlen(var)) == 0 && g_envp[i][ft_strlen(var)] == '=')
			expansion = ft_strdup(g_envp[i] + ft_strlen(var) + 1);
	}
	free(var);
	return (expansion);
}

int	ft_isinstring(char *string, char c)
{
	int	i;

	i = -1;
	while (string[++i])
		if (string[i] == c)
			return (1);
	return (0);
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

char	*get_var(char *token, int *i)
{
	char	*var;
	int		len;
	int		j;

	j = 0;
	len = 0;
	if (token[*i] == '$' && token[*i + 1] == '?')
	{
		var = ft_strdup("$?");
		return (var);
	}
	else if (ft_strncmp(&token[*i], "$?", 2) != 0 && token[*i] && token[*i + 1])
		(*i)++;
	j = *i;
	while (token[j] && (!ft_isspace(token[j]) && !ft_isinset(token[j], "$\"\'<>|")))
	{
		if (!ft_isinset(token[j], "{}"))
		{
			j++;
			len++;
		}
		else
			j++;
	}
	var = ft_calloc(len + 1, sizeof(char));
	j = 0;
	while (token[*i] && (!ft_isspace(token[*i]) && !ft_isinset(token[*i], "$\"\'<>|")))
	{
		if (ft_isinset(token[*i], "{}"))
			(*i)++;
		else
			var[j++] = token[(*i)++];
	}
	return (var);
}

char	*expand_new(char *token, char **g_envp)
{
	char	*expanded;
	char	*insert;
	char	*var;
	int		i;
	int		j;

	i = 0;
	if (!token)
		return (NULL);
	insert = NULL;
	expanded = NULL;
	while (token[i])
	{
		if (token[i] && !ft_isinset(token[i], "$\'\""))
			expanded = add_to_string(expanded, token[i]);
		else if (token[i] && ft_isinset(token[i], "\'"))
		{
			i++;
			while (token[i] && token[i] != '\'')
				expanded = add_to_string(expanded, token[i++]);
		}
		else if (token[i] && ft_isinset(token[i], "\""))
		{
			i++;
			while (token[i] && !ft_isinset(token[i], "$\""))
				expanded = add_to_string(expanded, token[i++]);
			while (token[i] && ft_isinset(token[i], "$"))
			{
				var = get_var(token, &i);
				if (ft_strncmp(var, "$?", 2) == 0)
					i += 2;
				insert = find_environment_variable(var, g_envp);
				if (!insert)
					continue ;
				j = 0;
				while (insert[j])
					expanded = add_to_string(expanded, insert[j++]);
				free(insert);
			}
			while (token[i] && !ft_isinset(token[i], "$\""))
				expanded = add_to_string(expanded, token[i++]);
		}
		else if (token[i] && ft_isinset(token[i], "$"))
		{
			var = get_var(token, &i);
			if (ft_strncmp(var, "$?", 2) == 0)
				i += 2;
			insert = find_environment_variable(var, g_envp);
			if (!insert)
				continue ;
			j = 0;
			while (insert[j])
				expanded = add_to_string(expanded, insert[j++]);
			while (token[i] && !ft_isinset(token[i], "$\""))
				expanded = add_to_string(expanded, token[i++]);
			if (token[i] == '$' && i != 0)
				i--;
			free(insert);
		}
		if (i < (int)ft_strlen(token))
			i++;
	}
	return (expanded);
}
