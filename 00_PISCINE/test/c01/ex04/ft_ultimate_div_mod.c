/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:04:33 by minkim            #+#    #+#             */
/*   Updated: 2021/02/15 14:14:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b)
{
	int temp;
	int temp2;

	temp = *a;
	temp2 = *b;
	*a = temp / temp2;
	*b = temp % temp2;
}

int		main(void)
{
	int a;
	int b;

	a = 11;
	b = 3;
	ft_ultimate_div_mod(&a, &b);
	printf("%d\n", a);
	printf("%d\n", b);
}
