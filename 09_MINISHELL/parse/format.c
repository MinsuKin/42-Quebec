/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 10:01:02 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_len_no_whitespace(char *line)
{
	int	i;
	int	new_len;

	new_len = 0;
	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (i == 0 && line[i] == ' ')
			i++;
		else if (line[i] == ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			i++;
		else
		{
			new_len++;
			i++;
		}
	}
	return (new_len);
}

// Make sure returns for NULL checks are adequate.
char	*remove_whitespace(char *line, int new_len)
{
	char	*new_string;
	int		i;
	int		j;

	if (!line)
		return (line);
	new_string = ft_calloc(new_len, sizeof(char) + 1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (i == 0 && line[i] == ' ')
			i++;
		else if (line[i] == ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			i++;
		else
		{
			new_string[j] = line[i];
			i++;
			j++;
		}
	}
	new_string[j] = '\0';
	return (new_string);
}

// this doesn't catch double ||, '', "", or |>>, <|>, etc.
// explore if this implementation needs to be revised
int	find_len_added_whitespace(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (ft_isinset(line[i], "|<>"))
		{
			if (line[i + 1] != ' ' && !ft_isinset(line[i + 1], "|<>"))
				count++;
			if (i != 0 && line[i - 1] != ' ' && !ft_isinset(line[i - 1], "|<>"))
				count++;
		}
		i++;
	}
	return (ft_strlen(line) + count);
}

// Make sure returns for NULL checks are adequate.
// this leaks somehow...
char	*add_whitespace(char *line, int new_len)
{
	char	*new_string;
	int		i;
	int		j;

	if (!line || line[0] == '\0')
		return (line);
	// why does !having_+2 cause memory errors?
	new_string = ft_calloc(new_len + 2, sizeof(char));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_isinset(line[i], "|<>") && (line[i - 1] != ' ' && !ft_isinset(line[i - 1], "|<>")))
			new_string[j++] = ' ';
		new_string[j] = line[i];
		if (line[i + 1] && ft_isinset(line[i], "|<>") && (line[i + 1] != ' ' && !ft_isinset(line[i + 1], "|<>\'\"")))
			new_string[++j] = ' ';
		i++;
		j++;
	}
	new_string[j] = '\0';
	return (new_string);
}

// Make sure returns for NULL checks are adequate.
// Prettify this function. Make sure free()s are done correctly.
char	*reformat_string(char *line)
{
	char	*new_string;
	char	*new_string_2;
	int		new_len;

	if (!line || line[0] == '\0')
		return (line);
	new_len = find_len_no_whitespace(line);
	new_string = remove_whitespace(line, new_len);
	free(line);
	new_len = find_len_added_whitespace(new_string);
	new_string_2 = add_whitespace(new_string, new_len);
	free(new_string);
	return (new_string_2);
}

// int	main(void)
// {
// 	char	*line;
// 	char	*r;

// 	line = ft_strdup("");
// 	r = reformat_string(line);
// 	printf("%s\n", r);
// 	free(r);
// }