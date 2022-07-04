/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:03:05 by tgarriss          #+#    #+#             */
/*   Updated: 2022/06/17 18:05:40 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// Allocate and return a new string resulting of concatenating s1 & s2.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	max_len;
	int		i;
	int		j;

	if (!s1)
		return ((char *) s2);
	if (!s2)
		return ((char *) s1);
	max_len = ft_strlen((char *) s1) + ft_strlen((char *) s2);
	result = (char *) malloc(max_len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i++] = s2[j];
	result[i] = '\0';
	return (result);
}
