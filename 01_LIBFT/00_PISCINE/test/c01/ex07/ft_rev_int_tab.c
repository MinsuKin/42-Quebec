/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:09:43 by minkim            #+#    #+#             */
/*   Updated: 2021/02/16 12:57:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int i;
	int temp;

	i = 0;
	while (i < (size / 2))
	{
		temp = tab[i];
		tab[i] = tab[size - 1 - i];
		tab[size - 1 - i] = temp;
		i++;
	}
}

int		main(void)
{
	int a[5] = { 1, 2, 3, 4, 5 };
	printf("%d, %d, %d, %d, %d", a[0], a[1], a[2], a[3], a[4]);
	ft_rev_int_tab(a, 5);
	printf("%d, %d, %d, %d, %d", a[0], a[1], a[2], a[3], a[4]);
}
