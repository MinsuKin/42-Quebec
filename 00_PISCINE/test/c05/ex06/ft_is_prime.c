/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 18:07:42 by minkim            #+#    #+#             */
/*   Updated: 2021/02/25 11:33:09 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_prime(int nb)
{
	int i;

	if (nb == 0 || nb == 1)
		return (1);
	if (nb == 2 || nb == 3)
		return (0);
	else
	{
		i = 2;
		if (nb % 2 == 0)
			return (0);
		i = 3;
		while (i <= nb / 3)
		{
			if (nb % i == 0)
				return (0);
			i = i + 2;
		}
	}
	return (1);
}

#include <stdio.h>
#include <math.h>


int		main(void)
{
	printf("%d\n", ft_is_prime(9));
	printf("%f\n", sqrt(4));
}