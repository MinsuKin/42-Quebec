/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:40:55 by minkim            #+#    #+#             */
/*   Updated: 2021/02/12 12:32:51 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_output(int a, int b)
{
	ft_putchar('0' + a / 10);
	ft_putchar('0' + a % 10);
	ft_putchar(' ');
	ft_putchar('0' + b / 10);
	ft_putchar('0' + b % 10);
	ft_putchar(',');
}

void	ft_print_comb2(void)
{
	int	a;
	int	b;

	a = 0;
	while (a <= 98)
	{
		b = a + 1;
		while (b <= 99)
		{
			print_output(a, b);
			b++;
		}
		a++;
	}
}

int		main(void)
{
	ft_print_comb2();
}
