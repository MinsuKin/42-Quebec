/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:38:03 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/28 15:08:45 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen((char *) s);
	if (*(s + len) == '\0' && (char )c == '\0')
		return ((char *)(s + len));
	while (len--)
	{
		if (*(s + len) == (char) c)
			return ((char *)(s + len));
	}
	return (NULL);
}
