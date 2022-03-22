/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:40:55 by minkim            #+#    #+#             */
/*   Updated: 2021/02/16 10:11:51 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print(char i, char j, char l)
{
	ft_putchar(i);
	ft_putchar(j);
	ft_putchar(l);
	if (i != '7')
	{
		ft_putchar(',');
		ft_putchar(' ');
	}
}

void	ft_print_comb(void)
{
	char i;
	char j;
	char l;

	i = '0';
	while (i <= '7')
	{
		j = i + 1;
		while (j <= '8')
		{
			l = j + 1;
			while (l <= '9')
			{
				ft_print(i, j, l);
				l++;
			}
			j++;
		}
		i++;
	}
}

int main()
{
	ft_print_comb();
}