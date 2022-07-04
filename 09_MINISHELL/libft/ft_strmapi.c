/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 12:01:53 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/20 12:41:10 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Take a given string, and apply the function to each of its characters.
// Returns a newly allocated string with the modified chars.
// the unsigned int arg for the fct pointer can be assumed to be the index
// where the char is at.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new_string;
	size_t	i;

	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *) s);
	new_string = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_string[i] = f(i, s[i]);
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
