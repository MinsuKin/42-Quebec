/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:11:50 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_environment_variable(char *var, char **envp)
{
	char	*expansion;
	int		i;

	if (!var || !envp)
		return (NULL);
	i = -1;
	expansion = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], &var[1], ft_strlen(var)) == 0)
		{
			if (envp[i][ft_strlen(var) - 1] == '=')
				expansion = ft_strdup(envp[i] + ft_strlen(var));
			else
				continue ;
		}
	}
	return (expansion);
}

// for when an environment variable doesn't exist.
char	*trim_var_from_string(char *line, char *var)
{
	char	*new_string;
	int		len_var;
	int		i;
	int		j;

	if (!line | !var)
		return (NULL);
	len_var = ft_strlen(var);
	new_string = ft_calloc(ft_strlen(line) - len_var + 1, sizeof(char));
	i = 0;
	j = -1;
	while (line[i])
	{
		if (ft_strncmp(&line[i], var, ft_strlen(var)) == 0)
			while (line[i] && line[i] != ' ')
				i++;
		if (line[i])
			new_string[++j] = line[i++];
	}
	return (new_string);
}

char	*insert_into_new_string(char *line, char *insert, char *var)
{
	char	*expanded;
	int		i;
	int		j;
	int		k;

	expanded = ft_calloc(ft_strlen(line) - ft_strlen(var) + ft_strlen(insert) + 1, sizeof(char));
	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (ft_strncmp(&line[i], var, ft_strlen(var)) == 0 && k == 0)
		{
			while (insert[k])
				expanded[j++] = insert[k++];
			k = 0;
			while (line[i] && line[i] == var[k] && var[k++])
				i++;
		}
		if (line[i])
			expanded[j++] = line[i++];
	}
	return (expanded);
}

char	*insert_var(char *line, char *var)
{
	char	*new_string;
	int		i;

	i = 0;
	while (ft_strncmp(&line[i], var, ft_strlen(var) == 0))
		i++;
	(void) new_string;
	return (line);
}

char	*expand_variable(char *line, char **envp, int index)
{
	char	*var;
	char	*expanded;
	char	*new_string;
	int		j;
	int		i;
	int		k;

	// if (within_single_quotes)
	// 	return (line); --> do not expand
	// what if its within_double_quotes
		// what then?
	i = index;
	// this check needs to be detailed. it's not only symbols, 
	// its much more, except quotes
	while (line[i] && (line[i] != ' '))
	{
		if (ft_isinset(line[i], "|<>"))
			break ;
		else
			i++;
	}
	var = ft_calloc((i - index) + 1, sizeof(char));
	j = 0;
	k = index;
	while (k < i)
		var[j++] = line[k++];
	expanded = find_environment_variable(var, envp);
	new_string = NULL;
	if (!expanded)
	 	new_string = trim_var_from_string(line, var);
	else
		new_string = insert_into_new_string(line, expanded, var);
	free(var);
	free(expanded);
	return (new_string);
}

void	check_for_quote(char *c, t_quotestruct *quotes)
{
	int	i;

	i = 1;
	if (!quotes->within_quotes)
	{
		if (c[0] == '\'' || c[0] == '\"')
		{
			while (c[i])
			{
				if (c[i] == c[0])
				{
					quotes->within_quotes = 1;
					quotes->quote_type = c[0];
					break ;
				}
				i++;
			}
		}
	}
	else if (quotes->within_quotes)
	{
		if (c[0] == quotes->quote_type)
		{
			quotes->within_quotes = 0;
			quotes->quote_type = '\0';
		}
	}
	return ;
}

// figure out how to develop $ARG to 'a file name'
// as in the case of $ARG="an argument" --> chmod a file name wouldn't work.
// we need quotes around it.
// that means modifying insert_into_new_string() 
// Also. Need to check for here_docs before doing any sort of expansion
// There could be an $ARG in the here_doc. it needs to be expanded too.
char	*expand(char *line, char **envp)
{
	t_quotestruct	*quotes;
	char			*temp;
	int				len;
	int				i;

	i = 0;
	len = ft_strlen(line);
	quotes = ft_calloc(1, sizeof(t_quotestruct));
	quotes->within_quotes = 0;
	quotes->quote_type = '\0';
	while (i < len)
	{
		// check for quotes, store somewhere, and pass to expansion
		check_for_quote(&line[i], quotes);
		if (i > 0 && line[i - 1] == '$')
			i--;
		// look at edgecase for "\$$"
		if (line[i] == '$')
		{
			temp = expand_variable(line, envp, i);
			//free(line);
			line = temp;
			len = ft_strlen(line);
		}
		i++;
	}
	free(quotes);
	return (line);
}

// extern char	**environ;
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*string;
// 	char	*new_string;

// 	(void) argc;
// 	(void) argv;
// 	(void) envp;
// 	string = ft_strdup("setenv '$ARG'");
// 	setenv("I", "i==3", 1);
// 	setenv("ARG", "an argument", 1);
// 	setenv("BLA", "BLARGUMENT", 1);
// 	new_string = expand(string, environ);
// 	printf("return: '%s'\n", new_string);
// 	free(new_string);
// }