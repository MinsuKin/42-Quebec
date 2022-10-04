/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:38:14 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/22 16:02:58 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Using CHARs here let us copy the entity byte per byte
// since CHARs are == to 1 byte. INTs would copy 4 bytes, floats... 
// Remember to account for NULL pointers. 
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*buffer;

	buffer = dst;
	if (!dst && !src)
		return (NULL);
	while (n)
	{
		*(char *) buffer = *(char *) src;
		buffer++;
		src++;
		n--;
	}
	return (dst);
}
