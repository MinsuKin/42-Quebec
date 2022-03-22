/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:13:34 by minkim            #+#    #+#             */
/*   Updated: 2021/02/27 16:18:36 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		*ft_range(int min, int max)
{
	int i;
	int n;
	int *s;

	if (min >= max)
		return (NULL);
	n = min - max;
	s = (int *)(malloc(sizeof(int) * -n));
	i = 0;
	while (min < max)
	{
		s[i] = min;
		i++;
		min++;
	}
	return (s);
}

int		main(void)
{
	int *i;

	i = ft_range(0, 3);
	printf("%d\n", *i);
	i++;
	printf("%d\n", *i);
	i++;
	printf("%d\n", *i);
	i++;
	printf("%d\n", *i);
}
