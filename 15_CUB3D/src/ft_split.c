/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:24:01 by chughes           #+#    #+#             */
/*   Updated: 2023/01/17 15:24:40 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Counts number of words in 's' based on 'c' seperator
static size_t	ft_wordcount(char const *s, char c)
{
	int				i;
	unsigned long	wordcount;

	i = 1;
	wordcount = 0;
	if (s == NULL || *s == '\0')
		return (wordcount);
	if (s[0] != c && s[0] != '\0')
		wordcount = 1;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			wordcount++;
		i++;
	}
	return (wordcount);
}

// Allocates return set of strings
static char	**makestrarray(unsigned int count)
{
	char	**rtn;

	rtn = (char **)xalloc(count + 1, sizeof(char *));
	if (rtn == NULL)
		return (NULL);
	rtn[count] = (void *)0;
	return (rtn);
}

// Splits 's' into multiple strings, 'c' is seperator
char	**ft_split(char const *s, char c)
{
	char			**rtn;
	unsigned int	wordcount;
	unsigned int	end;
	int				start;

	wordcount = ft_wordcount(s, c);
	rtn = makestrarray(wordcount);
	if (rtn == NULL || wordcount == 0)
		return (rtn);
	start = (unsigned int)ft_strlen(s) - 1;
	while (s[start] && start >= 0)
	{
		while (s[start] && start > 0 && s[start] == c)
			start--;
		end = start;
		while (s[start] && start > 0 && s[start] != c)
			start--;
		wordcount--;
		if (start == 0)
			start -= 1;
		rtn[wordcount] = ft_substr(s, start + 1, (end - start));
		if (wordcount == 0)
			break ;
	}
	return (rtn);
}
