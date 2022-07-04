/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 09:50:24 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/22 15:02:11 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compares to byte(?)-strings and returns 0 if the strings are identical,
// or the difference between the first two differing bytes. It is assumed
// that the strings are BOTH n bytes long.
// Remember to coerce the void pointers into strings, because using it as
// void pointers is unworkable.
// RENAME VARIABLES. they're != strings, they're memory spaces. Use PTR or
// something...
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*bstring1;
	unsigned char	*bstring2;

	i = 0;
	bstring1 = (unsigned char *) s1;
	bstring2 = (unsigned char *) s2;
	while (i < n)
	{
		if (*bstring1 != *bstring2)
			return (*bstring1 - *bstring2);
		i++;
		bstring1++;
		bstring2++;
	}
	return (0);
}
