/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:10:21 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/22 13:42:57 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// -->	write zeroes to a byte string. The bzero() function writes
// n zeroed bytes to the string s.  If n is zero, bzero() does nothing.

// void pointers are unassignable, typecast it to a (char *)
void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = (char *) s;
	if (n == 0)
		return ;
	while (i < n)
	{
		buffer[i] = 0;
		i++;
	}
}
