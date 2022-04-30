/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 10:50:57 by minkim            #+#    #+#             */
/*   Updated: 2021/02/25 15:02:57 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_is_prime(int nb)
{
	int i;

	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (0);
	if (nb == 2 || nb == 3)
		return (1);
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

int		ft_find_next_prime(int nb)
{
	if (nb < 3)
		return (2);
	else
	{
		while (ft_is_prime(nb) == 0)
			nb++;
		return (nb);
	}
}
