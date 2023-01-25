/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:41:49 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:42:16 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Returns a copy of 's' starting at 'start' and of length 'len'
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	const char	*first;

	first = &s[start];
	str = xalloc((len + 1), sizeof(char));
	if (start > ft_strlen(s))
		return (str);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, first, (len + 1));
	str[len] = '\0';
	return (str);
}
