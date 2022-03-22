/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:16:37 by minkim            #+#    #+#             */
/*   Updated: 2021/06/11 11:30:32 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	res;
	size_t	source;

	res = 0;
	source = 0;
	while (dst[res] && res < dstsize)
		res++;
	while (src[source] && ((res + source + 1) < dstsize))
	{
		dst[res + source] = src[source];
		source++;
	}
	if (res != dstsize)
		dst[res + source] = '\0';
	return (res + ft_strlen(src));
}
