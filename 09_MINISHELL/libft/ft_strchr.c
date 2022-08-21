/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:20:23 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/14 15:24:10 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	
	i = 0;
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	if (*s == '\0' && (char) c == '\0')
		return ((char *) s);
	return (NULL);
}
