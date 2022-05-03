/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:13:34 by minkim            #+#    #+#             */
/*   Updated: 2021/03/03 13:19:46 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int i;
	int n;
	int *s;

	if (min >= max)
		return (NULL);
	n = min - max;
	if (!(s = (int *)(malloc(sizeof(int) * -n))))
		return (0);
	i = 0;
	while (min < max)
	{
		s[i] = min;
		i++;
		min++;
	}
	return (s);
}
