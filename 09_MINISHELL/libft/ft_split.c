/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:40:45 by tgarriss          #+#    #+#             */
/*   Updated: 2021/10/26 11:09:29 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_strings(char const *s, char c)
{
	int	num;
	int	index;

	num = 0;
	index = 0;
	while (s[index] && s[index] == c)
		index++;
	while (s[index])
	{
		if (s[index] == c)
		{
			num++;
			while (s[index] && s[index] == c)
				index++;
			continue ;
		}
		index++;
	}
	if (index != 0)
		if (s[index - 1] != c)
			num++;
	return (num);
}

// Everytime this function starts, index at the offset, and check if the 
// character there is a delimiter. Increment.
// When it stops, you're at a character. So start incrementing until you find
// another delimiter.
// Calculate the difference between the end - 
static char	*make_strings(char *string, int *offset, char delim)
{
	int		start;
	char	*word;
	int		index;

	while (string[*offset] == delim)
		(*offset)++;
	start = *offset;
	while (string[*offset] && string[(*offset) + 1] != delim)
		(*offset)++;
	word = malloc(sizeof(char) * (*offset - start + 1) + 1);
	index = 0;
	while (start <= *offset)
	{
		word[index] = string[start];
		index++;
		start++;
	}
	*offset += 1;
	word[index] = '\0';
	return (word);
}

// Do a NULL-check
// get number of strings and allocate the necessary memory. Do a NULL-check.
// i == index of split. offset == index of the string. It gets passed as an
// address so that the other function can modify it.
// Use make_strings to fill the array. make_strings takes the string, the offset
// (at start == 0), and the delimiter. SEE ABOVE.
char	**ft_split(char const *s, char c)
{
	char	**split;
	int		num_strings;
	int		i;
	int		offset;

	if (!s)
		return (NULL);
	num_strings = get_num_strings(s, c);
	split = (char **) malloc((num_strings + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	offset = 0;
	while (i < num_strings)
	{
		split[i] = make_strings((char *) s, &offset, c);
		i++;
	}
	split[i] = NULL;
	return (split);
}
