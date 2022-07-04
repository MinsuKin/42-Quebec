/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:31:35 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_quotestruct	init_quotestruct(void)
{
	t_quotestruct	q;

	q.within_quotes = 0;
	q.quote_type = '\0';
	return (q);
}

// None of the functions called here check if they're within quotes,
// which would negate any errors found. i.e. 'ls | echo ">> <<" | grep "|"
int	check_syntax_valid(char *line)
{
	int	valid;

	valid = 1;
	if (!line)
		return (valid);
	if (find_num_of_quotes(line, init_quotestruct()) % 2)
		valid = 0;
	if (!check_pipe_format_valid(line))
		valid = 0;
	if (!check_redirection_valid(line))
		valid = 0;
	return (valid);
}

int	check_pipe_format_valid(char *line)
{
	int	valid;
	int	i;

	i = 0;
	valid = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_isalpha(line[i]))
			valid = 1;
		if (!valid && line[i] == '|')
			return (0);
		else if (line[i] == '|' && valid)
			valid = 0;
		i++;
	}
	return (valid);
}

// https://stackoverflow.com/questions/6697753/difference-between-single-and-double-quotes-in-bash
// this segment of code must be rewritten. It is insufficient to merely check for # of quotes.
// This will require rebuilding strings in some regard.
int	find_num_of_quotes(char *line, t_quotestruct q)
{
	int	num;
	int	i;

	i = -1;
	num = 0;
	if (!line)
		return (num);
	while (line[++i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !q.within_quotes)
		{
			q.within_quotes = 1;
			q.quote_type = line[i];
			num++;
		}
		else if (line[i] == q.quote_type)
		{
			q.within_quotes = 0;
			q.quote_type = line[i];
			num++;
		}
	}
	return (num);
}

int	check_redirection_valid(char *line)
{
	int	valid;
	int	i;
	int	j;

	if (!line)
		return (0);
	i = -1;
	j = -1;
	valid = 1;
	while (line[++i])
	{
		if (line[i] && (line[i] == '>' || line[i] == '<'))
		{
			valid = 0;
			j = i + 1;
			if (line[j] && (line[j] == '>' || line[j] == '<'))
				j++;
			while (line[++j] && line[j] != '|')
				if (ft_isalpha(line[j]))
					valid = 1;
		}
		if (!valid)
			return (0);
	}
	return (valid);
}

// int	main(void)
// {
// 	char	*string;

// 	string = ft_strdup("echo $ARG | stuff < infile");
// 	check_syntax_valid(string);
// 	free(string);
// }