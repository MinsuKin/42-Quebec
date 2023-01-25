/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:38:08 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:38:39 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Allocates and duplicates 'src'
char	*ft_strdup(const char *src)
{
	char	*outstr;
	size_t	len;
	size_t	i;

	if (src == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(src);
	if (len == 0)
		return (NULL);
	outstr = xalloc((len + 1), sizeof(char));
	if (outstr == NULL)
		return (NULL);
	while (i < len)
	{
		outstr[i] = src[i];
		i++;
	}
	return (outstr);
}
