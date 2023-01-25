/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:10:27 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 15:12:59 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Returns allocated copy of str with char at pos deleted, frees str
char	*strpop(char *str, int position)
{
	char	*new_str;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	new_str = (char *)xalloc(ft_strlen(str), sizeof(char));
	if (position < 0)
		position += ft_strlen(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (i != position)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	xfree(str);
	return (new_str);
}
