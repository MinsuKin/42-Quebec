/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:24:36 by minkim            #+#    #+#             */
/*   Updated: 2021/02/24 12:25:18 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		plusmi(char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int		doublechar(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int i;

	i = 0;
	while (base[i])
		i++;
	if (i > 1 && plusmi(base) == 1 && doublechar(base) == 1)
	{
		if (nbr == -2147483648)
		{
			ft_putnbr_base((nbr / i), base);
			write(1, &base[nbr % i * -1], 1);
		}
		else if (nbr < 0)
		{
			write(1, "-", 1);
			ft_putnbr_base(-nbr, base);
		}
		else if (nbr < i)
			write(1, &base[0 + nbr], 1);
		else
		{
			ft_putnbr_base((nbr / i), base);
			ft_putnbr_base((nbr % i), base);
		}
	}
}

int		main(void)
{
	ft_putnbr_base(-2147483648, "0123456789ABCDEF");
	putchar('\n');
	ft_putnbr_base(-2147483648, "0123456789");
	putchar('\n');
	ft_putnbr_base(-2147483648, "poneyvif");
	putchar('\n');
	ft_putnbr_base(-2147483648, "01");
	putchar('\n');
}
