/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:47:48 by minkim            #+#    #+#             */
/*   Updated: 2021/03/03 13:18:56 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strcpy(char *dest, char *src)
{
	unsigned long i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*s2;

	i = 0;
	while (src[i])
		i++;
	if (!(s2 = (char *)malloc(sizeof(char) * i)))
		return (0);
	if (s2)
		ft_strcpy(s2, src);
	return (s2);
}
