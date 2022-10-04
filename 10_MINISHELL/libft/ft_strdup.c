/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:11:59 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/11 10:15:38 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_strdup allocates enough memory for the string s1, does the copy
// and returns a pointer to the copy. Always NULL-terminates the string.
// first, find the length. second, malloc + 1. third, copy. four, return.
char	*ft_strdup(const char *s1)
{
	char	*copy;
	char	*start;
	size_t	len;

	len = ft_strlen((char *) s1);
	copy = malloc(len + 1);
	if (!copy)
	{
		free(copy);
		return (NULL);
	}
	start = copy;
	while (len--)
	{
		*copy = *s1;
		copy++;
		s1++;
	}
	*copy = '\0';
	return (start);
}
