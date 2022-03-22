/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:29:00 by minkim            #+#    #+#             */
/*   Updated: 2021/06/10 10:04:23 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	dest = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dest < s)
	{
		while (len--)
			*dest++ = *s++;
	}
	else
	{
		while (len--)
			*(dest + len) = *(s + len);
	}
	return (dst);
}
