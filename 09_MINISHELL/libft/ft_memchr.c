/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:25:15 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/22 14:56:35 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Locates byte in byte string
// Looks for the INT c (converted to UNSIGNED CHAR) in VOID pointer s.
// convert the void* to an unsigned char* to look byte per
// byte /--> sizeof(char) == 1 byte. 

// The memchr() function returns a pointer to the byte located, or NULL
// if no such byte exists within n bytes.
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;

	string = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (*string == (unsigned char) c)
			return (string);
		string++;
		i++;
	}
	return (NULL);
}
