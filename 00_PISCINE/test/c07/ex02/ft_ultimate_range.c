/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:16:03 by minkim            #+#    #+#             */
/*   Updated: 2021/03/03 17:21:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int		ft_ultimate_range(int **range, int min, int max)
{
	int i;
	int n;
	int *s;

	if (min >= max)
		return (0);
	n = max - min;
	if (!(s = (int *)(malloc(sizeof(int) * n))))
		return (-1);
	i = 0;
	while (min < max)
	{
		s[i] = min;
		i++;
		min++;
	}
	*range = s;
	return (n);
}

int		main(void)
{
	int *i;
	int j;

	j = ft_ultimate_range(&i, 0, 3);
	printf("%d\n", *i);
	i++;
	printf("%d\n", *i);
	i++;
	printf("%d\n", *i);
	i++;
	printf("%d\n", *i);	
	i++;
	printf("%d\n", j);	
}
