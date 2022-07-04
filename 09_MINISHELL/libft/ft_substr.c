/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:15:42 by tgarriss          #+#    #+#             */
/*   Updated: 2022/06/19 17:32:50 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_substr returns a copy of a subset of a string. It calls ft_strlcpy
// which NULL-terminates the string.

// Remember to protect the function against faulty input.
// Check if the length of s is less than the index where to start duplicating.
// If it is, you've reached the end of the string: return an empty string.
// if it turns out that new_len is less than len. Save space and use
// the new_len for calculating the rest. Couldn't one just use new_len
// instead?
// use ft_strlcpy to make a copy of the string and NULL-terminate it.
// dst is the newly created string, src is s + start, and the dst size
// is the calculated size from above + space for the '\0'.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	new_len;

	if (!s)
		return (NULL);
	if (start > ft_strlen((char *) s))
		return (ft_strdup(""));
	new_len = ft_strlen((char *) s + start);
	if (new_len < len)
		len = new_len;
	substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *)s + start, len + 1);
	return (substr);
}
