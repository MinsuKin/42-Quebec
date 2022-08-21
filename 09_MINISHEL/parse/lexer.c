/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:18:36 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/19 19:23:25 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (!line)
		return (NULL);
	tokens = tokenizer(line);
	// ft_print_sarray(tokens);
	table = set_commandtable(tokens);
	// print_command_table(table);
	if (tokens)
		ft_free_carray(tokens);
	return (table);
}

void	close_files(t_iarray *files)
{
	int	i;

	if (!files)
		return ;
	i = -1;
	while (++i < files->size)
		close(files->array[i]);
	files->size = 0;
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
		j = 0;
		while (j < table->commands[i].num_args)
		{
			free(table->commands[i].arguments[j]);
			j++;
		}
		free(table->commands[i].arguments);
		i++;
	}
	if (table->open_files)
	{
		close_files(table->open_files);
		free(table->open_files->array);
		free(table->open_files);
	}
	unlink("heredoc");
	free(table->commands);
	free(table);
}
