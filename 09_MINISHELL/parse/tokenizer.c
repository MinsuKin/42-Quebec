/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:16:34 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/18 13:25:42 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	ft_print_sarray(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		printf("'%s'\n", array[i]);
}

char	*make_token(char *start, char *end)
{
	char	*token;
	int		i;

	if (!start)
		return (NULL);
	i = 0;
	while (start[i] != *end)
		i++;
	token = ft_calloc(i + 1, sizeof(char));
	i = -1;
	while (start[++i] != *end)
		token[i] = start[i];
	if (!ft_strlen(token))
	{
		free(token);
		return (NULL);
	}
	return (token);
}

// quotes haven't been removed yet.
// quotes aren't working super great either... getting some errors on unclo
// otherwise, it seems to work just fine... neaaaaat!
char	*find_match(char *line, char *characters)
{
	static char	*start;
	static bool	matched;
	char		*token;
	int			i;
	int			j;

	if (!line || !characters)
		return (NULL);
	token = NULL;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_isinset(line[i], characters) && !matched)	// if you haven't found one of the 'characters' yet.
	{
		token = make_token(start, &line[i]);
		start = &line[i];
		matched = true;
		return (token);
	}
	else if (ft_isinset(line[i], characters) && matched)	// if you have found one of the 'characters'
	{
		j = i + 1;
		if (ft_isinset(line[i], "$"))	// you've found an expansion
		{
			if (line[i + 1] != '$' && line[i + 1] != '?')
			{
				while (line[j] && (ft_isinset(line[j], "{}") || ft_isalnum(line[j])))
					j++;
			}
			else
			{
				while (line[j] && !ft_isspace(line[j]))
					j++;
			}
		}
		else if (ft_isinset(line[i], "\'\"")) // you found a quote
		{
			while (line[j])
			{
				if (line[j] == line[i])
					break ;
				j++;
			}
			j++;
			while (ft_isalnum(line[j]) && !ft_isinset(line[j], "<>|$() \t"))
				j++;
		}
		else if (ft_isinset(line[i], "-"))
		{
			while (line[j] && !ft_isspace(line[j]))
				j++;
		}
		else	// you're matching a series of delimiters
		{
			while (line[j] && line[j] == line[i])
				j++;
		}
		token = make_token(&line[i], &line[j]);
		while (ft_isspace(line[j]))
			j++;
		start = &line[j];
		matched = false;
		return (token);
	}
	else if (ft_isalnum(line[i]))	// else alnum
	{
		j = i + 1;
		while (line[j] && !ft_isspace(line[j]))
		{
			if (ft_isinset(line[j], "\""))
			{
				j++;
				while (line[j] && line[j] != '\"')
					j++;
			}
			if (ft_isinset(line[j], "\'"))
			{
				j++;
				while (line[j] && line[j] != '\'')
					j++;
			}
			else
				j++;
		}
		token = make_token(&line[i], &line[j]);
		while (ft_isspace(line[j]))
			j++;
		start = &line[j];
		matched = true;
		return (token);
	}
	else
	{
		// printf("catching tokenization else\n");
		j = i + 1;
		while (line[j] && !ft_isinset(line[j], "<>|() \t"))
			j++;
		token = make_token(&line[i], &line[j]);
		start = &line[j];
		matched = true;
	}
	return (token);
}

int	find_empty_line(char *line)
{
	int	length;
	int	num_spaces;
	int	i;

	if (!line)
		return (1);
	length = ft_strlen(line);
	if (!length)
		return (1);
	i = 0;
	num_spaces = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			num_spaces++;
		i++;
	}
	if (num_spaces == i)
		return (1);
	return (0);
}

char	**tokenizer(char *line)
{
	char		**tokens;
	char		*token;
	int			i;

	if (find_empty_line(line))
		return (NULL);
	i = 0;
	tokens = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		token = find_match(&line[i], "<>|()* \t\'\"-");
		i += ft_strlen(token);
		if (token)
		{
			tokens = ft_add_to_sarray(tokens, token, 1);
		}
		while (line[i] && ft_isspace(line[i]))
			i++;
	}
	// printf("tokens\n");
	// ft_print_sarray(tokens);
	return (tokens);
}

// int	main(int argc, char **argv)
// {
// 	char	**array;

// 	if (argc != 2)
// 		ft_error("bad usage.", __FILE__, __func__, __LINE__);
// 	array = tokenizer(argv[1]);
// 	ft_print_sarray(array);
// }