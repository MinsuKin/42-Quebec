/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:41:53 by minkim            #+#    #+#             */
/*   Updated: 2021/03/03 14:48:49 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		size_for_new_string(int size, char **strs, char *sep)
{
	int		final_size;
	int		i;

	i = 0;
	final_size = 0;
	while (i < size)
	{
		final_size = final_size + ft_strlen(strs[i]);
		if (i < size - 1)
			final_size = final_size + ft_strlen(sep);
		i++;
	}
	return (final_size);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*copy;
	int		i;
	int		new_string_size;

	new_string_size = size_for_new_string(size, strs, sep);
	if (!(copy = (char *)malloc(sizeof(char) * (new_string_size + 1))))
		return (0);
	i = 0;
	while (i < size)
	{
		ft_strcat(copy, strs[i]);
		if (i < size - 1)
			ft_strcat(copy, sep);
		i++;
	}
	return (copy);
}
