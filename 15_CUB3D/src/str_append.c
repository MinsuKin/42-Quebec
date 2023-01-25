/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:44:04 by chughes           #+#    #+#             */
/*   Updated: 2023/01/14 16:56:41 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Prepends 's1' to 's2' and frees 's1'
char	*str_append(char *s1, char *s2)
{
	char	*rtn;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (s2[0] == '\0')
		return (s1);
	rtn = xalloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	while (s1[++i])
		rtn[i] = s1[i];
	while (s2[++j])
		rtn[i + j] = s2[j];
	s1 = xfree(s1);
	return (rtn);
}
