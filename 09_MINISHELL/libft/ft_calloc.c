/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:47:22 by tgarriss          #+#    #+#             */
/*   Updated: 2022/05/17 06:52:04 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// calloc allocates enough memory for count * size, and fills the
// memory location with zeros (uses bzero). It returns a pointer to the start
// of the allocated memory. 
void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*mem;

	bytes = count * size;
	mem = malloc(sizeof(char) * bytes);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, bytes);
	return (mem);
}
