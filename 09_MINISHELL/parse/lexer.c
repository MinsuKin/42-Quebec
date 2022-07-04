/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:18:36 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// extern char **environ;

int	get_num_commands(char **tokens)
{
	int	count;
	int	i;

	if (!tokens)
		return (-1);
	i = -1;
	count = 1;
	while (tokens[++i])
		if (tokens[i][0] == '|' && ft_strlen(tokens[i]) == 1)
			count++;
	return (count);
}

t_commandtable	*parse(char *line)
{
	char			**tokens;
	t_commandtable	*table;
	char			*string;

	if (!line)
		return (NULL);
	string = reformat_string(line);
	tokens = tokenize(string);
	free(string);
	table = set_commandtable(tokens);
	// if (tokens)
	// 	free(tokens);
	return (table);
}

void	free_commandtable(t_commandtable *table)
{
	int	i;
	int	j;

	if (!table)
		return ;
	i = 0;
	while (i < table->num_commands)
	{
		free(table->commands[i].command);
		j = -1;
		while (++j < table->commands[i].num_args)
			free(table->commands[i].arguments[j]);
		i++;
	}
	if (table->open_files)
	{
		free(table->open_files->array);
		free(table->open_files);
	}
	free(table->commands);
	free(table);
}

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	setenv("ARG", "ARGUMENT", 1);
// 	parse("echo \"$ARG\">>outfile|grep bla");
// }
