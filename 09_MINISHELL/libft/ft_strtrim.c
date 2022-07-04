/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:00:56 by tgarriss          #+#    #+#             */
/*   Updated: 2021/10/21 11:39:46 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Remember to do a NULL-check.
// Use ft_strchr to compare the set (string) against each char of s1.
// having incremented the pointer, you can calculate the size of the string
// not counting the set. 
// use the max size of the string, to count from the end, going backwards
// and checking if each char is contained within the set.
// then use ft_strdup to make a duplicate. Since the pointer is STILL after
// the first incrementation, the start index is 0, the len is size + '\0'
// return the newly trimmed string.

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, s1[size]))
		size--;
	trimmed = ft_substr(s1, 0, size + 1);
	return (trimmed);
}
