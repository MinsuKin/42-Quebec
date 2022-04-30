/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 10:50:29 by minkim            #+#    #+#             */
/*   Updated: 2021/02/25 11:54:10 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_power(int nb, int power)
{
	int i;
	int j;

	i = power;
	j = nb;
	if (power == 0)
		return (1);
	else if (nb >= -2147483648 && nb <= 2147483647 && power > 0)
	{
		while (i-- > 1)
			nb = nb * j;
		return (nb);
	}
	else
		return (0);
}
