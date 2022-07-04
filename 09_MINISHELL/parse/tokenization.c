/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:01:09 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_command(t_command *command)
{
	command->command = NULL;
	command->binary = NULL;
	command->options = NULL;
	command->arguments = NULL;
	command->num_args = 0;
	command->input = STDIN_FILENO;
	command->output = STDOUT_FILENO;

}

char	**add_to_array(char **array, char *insert)
{
	char	**new_array;
	int		i;

	// if (!insert)
	// 	return (array);
	new_array = ft_calloc(ft_get_array_length(array) + 2, sizeof(char *));
	i = 0;
	if (array)
	{
		while (array[i])
		{
			new_array[i] = ft_strdup(array[i]);
			free(array[i]);
			i++;
		}
	}
	new_array[i] = ft_strdup(insert);
	free(insert);
	free(array);
	// if (array)
	// 	ft_free_carray(array);
	return (new_array);
}

char	**tokenize(char *line)
{
	char			**array;
	t_quotestruct	quotes;
	char			*token;
	int				stop;
	int				i;

	if (!line || line[0] == '\0')
		return (NULL);
	i = 0;
	stop = 0;
	array = NULL;
	token = NULL;
	quotes.quote_type = '\0';
	quotes.within_quotes = 0;
	while (line[i])
	{
		check_for_quote(&line[i], &quotes);
		if (quotes.within_quotes)
		{
			stop = i;
			stop++;
			while (line[stop] != quotes.quote_type && line[stop])
				stop++;
			if (line[stop] == quotes.quote_type)
			{
				quotes.within_quotes = 0;
				stop++;
			}
			token = ft_calloc(stop - i + 1, sizeof(char));
			ft_strlcpy(token, &line[i], stop - i + 1);
			if (ft_strlen(token))
				array = add_to_array(array, token);
			if (line[stop + 1] && !ft_isspace(line[stop + 1]) && stop - 1 >= 0)
				i = stop - 1;
			else
				i = stop;
		}
		else
		{
			while (line[i] && ft_isspace(line[i]))
				i++;
			stop = i;
			if (line[stop] && ft_isinset(line[stop], "|"))
			{
				while (line[stop] && ft_isinset(line[stop], "|"))
					stop++;
				token = ft_calloc(stop - i + 1, sizeof(char));
				ft_strlcpy(token, &line[i], stop - i + 1);
				array = add_to_array(array, token);
				i = stop;
				if (line[stop + 1] && !ft_isspace(line[stop + 1]) && stop - 1 >= 0)
					i = stop - 1;
			}
			else
			{
				while (!ft_isspace(line[stop]) && !ft_isinset(line[stop], "|") && line[stop])
					stop++;
				token = ft_calloc(stop - i + 1, sizeof(char));
				ft_strlcpy(token, &line[i], stop - i + 1);
				if (ft_strlen(token))
					array = add_to_array(array, token);
				if (line[stop] && ft_isinset(line[stop], "|") && stop - 1 >= 0)
					i = stop - 1;
				else
					i = stop;
			}
		}
		i++;
	}
	return (array);
}

// int	main(void)
// {
// 	// char	**array;
// 	t_commandtable	*table;
// 	char	*string;

// 	string = ft_strdup("echo $ARG | < outfile cat | grep stuff > infile");
// 	table = parse(string);
// 	// array = tokenize(string);
// 	// int	i;

// 	// i = 0;
// 	// while (array[i])
// 	// {
// 	// 	printf("'%s'\n", array[i]);
// 	// 	i++;
// 	// }
// 	//free(string);
// 	//free_commandtable(table);
// 	//ft_free_carray(array);
// }