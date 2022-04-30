/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:16:40 by minkim            #+#    #+#             */
/*   Updated: 2021/02/24 10:50:00 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_factorial(int nb)
{
	int i;

	i = nb;
	if (nb >= 1 && nb <= 2147483647)
	{
		while (i > 1)
			nb = nb * --i;
		return (nb);
	}
	else if (nb == 0)
		return (1);
	else
		return (0);
}
