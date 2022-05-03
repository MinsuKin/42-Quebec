/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2 copy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:40:55 by minkim            #+#    #+#             */
/*   Updated: 2021/02/16 13:45:57 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print(char i, char j, char l, char y)
{
	if (((i * 10) + j) < ((l * 10) + y))
	{
		ft_putchar(i);
		ft_putchar(j);
		ft_putchar(' ');
		ft_putchar(l);
		ft_putchar(y);
		if (((i * 10) + j) < (('9' * 10) + '8'))
		{
			ft_putchar(',');
			ft_putchar(' ');
		}
	}
}

void	ft_print_comb(char i, char j, char l, char y)
{
	i = '0';
	while (i <= '9')
	{
		j = '0';
		while (j <= '9')
		{
			l = '0';
			while (l <= '9')
			{
				y = '0';
				while (y <= '9')
				{
					ft_print(i, j, l, y);
					y++;
				}
				l++;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_comb2(void)
{
	ft_print_comb('0', '0', '0', '0');
}

int main()
{
	ft_print_comb2();
}