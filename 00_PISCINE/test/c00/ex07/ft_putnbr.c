/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:46:58 by minkim            #+#    #+#             */
/*   Updated: 2021/02/16 13:07:53 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb != -2147483648)
	{
		if (nb < 0)
		{
			ft_putchar('-');
			ft_putnbr(-nb);
		}
		else if (nb < 10)
		{
			ft_putchar('0' + nb);
		}
		else
		{
			ft_putnbr(nb / 10);
			ft_putnbr(nb % 10);
		}
	}
	else
		write(1, "-2147483648", 11);
		// write(1, "-2147483648", sizeof("-2147483648"));
		// printf("Size of variable a : %lu\n",sizeof("-2147483648"));
}

int main()
{
	ft_putnbr(42);
	// char *i = "-2147483648";
	// printf("Size of variable a : %c\n", i[11]);
}
