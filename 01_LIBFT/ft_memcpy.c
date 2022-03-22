/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 13:57:47 by minkim            #+#    #+#             */
/*   Updated: 2021/06/10 10:04:17 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*s;

	dest = (char *)dst;
	s = (const char *)src;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*dest++ = *s++;
	return (dst);
}
