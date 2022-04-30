/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:42:43 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/01 10:21:17 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bsq.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str++)
	{
		write(1, str - 1, 1);
	}
}

void	ft_putnbr(int nb)
{
	long x;

	x = nb;
	if (x < 0)
	{
		ft_putchar('-');
		x = -x;
	}
	if (x > 9)
	{
		ft_putnbr(x / 10);
		ft_putnbr(x % 10);
	}
	else
	{
		ft_putchar(x + 48);
	}
}
