/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 08:52:20 by tgarriss          #+#    #+#             */
/*   Updated: 2022/06/24 13:05:25 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strlcpy copies a string src to string dst up to the specified
// destsize, and returns the length of src.
// It always NULL-terminates if dstsize is not 0
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	index;

	if (!src)
		return (0);
	count = 0;
	index = 0;
	while (src[count] != '\0')
		count++;
	if (dstsize != 0)
	{
		while (src[index] != '\0' && index < (dstsize - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (count);
}
