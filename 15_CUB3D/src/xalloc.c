/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:45 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:46:15 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Sets 'n' bytes of memory to 0x0 at 's' address
static inline void	ft_bzero(void *s, size_t n)
{
	size_t	count;
	char	*str;

	str = (char *)s;
	count = 0;
	while (count < n)
	{
		str[count] = 0;
		count++;
	}
	return ;
}

// Calls malloc and bzero on the allocated memory
void	*xalloc(size_t nitems, size_t size)
{
	void	*outptr;

	outptr = malloc(nitems * size);
	if (outptr == NULL)
		return (NULL);
	ft_bzero(outptr, (nitems * size));
	return (outptr);
}

// Calls free(ptr) and returns a NULL pointer
void	*xfree(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	return (NULL);
}
