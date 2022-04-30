/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:50:29 by minkim            #+#    #+#             */
/*   Updated: 2021/02/24 14:26:25 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_recursive_power(int nb, int power)
{
	int j;

	j = nb;
	if (power == 0)
		return (1);
	else if (nb >= -2147483648 && nb <= 2147483647 && power > 0)
		return (nb * ft_recursive_power(j, --power));
	else
		return (0);
}

int		main(void)
{
	printf("%d", ft_recursive_power(-5, 3));
}
