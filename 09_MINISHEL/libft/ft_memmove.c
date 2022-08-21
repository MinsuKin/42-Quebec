/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 14:34:28 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/22 16:22:50 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// memmove is similar to memcpy, but it accounts for memory overlap. 
// If the destination memory location is "higher" than the source
// memory location, copying from back-to-front avoids overwriting what
// you are moving.
// Otherwise, if source > dest, it behaves exactly as memcpy, and thus
// copies from front-to-back.
// the use of (char *) casts allows to copy stuff; void pointers are 
// unassignable.
// 
// Look at the following link for more detailled explanations.
// https://stackoverflow.com/questions/1201319/what-is-the-difference
// -between-memmove-and-memcpy
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *) src;
	d = (char *) dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
