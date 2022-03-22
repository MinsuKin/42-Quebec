/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 07:03:35 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/04 07:51:12 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_header.h>

int		ft_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == 0)
		return (1);
	return (0);
}

int		ft_nbr_words(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (ft_sep(str[i + 1], charset) == 1 && ft_sep(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

void	ft_word_tab(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	while (ft_sep(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = 0;
}

void	ft_resolve(char **res, char *str, char *charset)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		if (ft_sep(str[i], charset) == 1)
			i++;
		else
		{
			while (ft_sep(str[i + j], charset) == 0)
				j++;
			res[k] = malloc(sizeof(char) * (j + 1));
			ft_word_tab(res[k], str + i, charset);
			i += j;
			k++;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	int		count;

	count = ft_nbr_words(str, charset);
	res = malloc(sizeof(char *) * (count + 1));
	res[count] = 0;
	ft_resolve(res, str, charset);
	return (res);
}
