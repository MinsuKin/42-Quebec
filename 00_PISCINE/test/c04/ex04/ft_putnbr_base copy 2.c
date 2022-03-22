/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:24:36 by minkim            #+#    #+#             */
/*   Updated: 2021/02/23 13:30:38 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	todecimal(int num)
{
	char *base;

	base = "0123456789";
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	if (num > 0)
	{
		todecimal(num / 10);
		write(1, &(base[num % 10]), 1);
	}
}

void	tobinary(int num)
{
	char *base;

	base = "01";
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	if (num > 0)
	{
		tobinary(num / 2);
		write(1, &(base[num % 2]), 1);
	}
}

void	tohexa(int num)
{
	char *base;

	base = "0123456789ABCDEF";
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	if (num > 0)
	{
		tohexa(num / 16);
		write(1, &(base[num % 16]), 1);
	}
}

void	tooctal(int num)
{
	char *base;

	base = "01234567";
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	if (num > 0)
	{
		tooctal(num / 8);
		write(1, &(base[num % 8]), 1);
	}
}

void	ft_putnbr_base(int nbr, char *base)
{
	if (nbr == 0)
		write(1, "0", 1);
	else
	{
		if (ft_strcmp(base, "0123456789ABCDEF") == 0)
			tohexa(nbr);
		else if (ft_strcmp(base, "0123456789") == 0)
		{
			if (nbr < 0)
			{
				write(1, "-", 1);
				ft_putnbr_base(-nbr, "0123456789");
			}
			else if (nbr < 10)
				write(1, &base[0 + nbr], 1);
			else
			{
				ft_putnbr_base((nbr / 10), "0123456789");
				ft_putnbr_base((nbr % 10), "0123456789");
			}
		}
		else if (ft_strcmp(base, "poneyvif") == 0)
			tooctal(nbr);
		else if (ft_strcmp(base, "01") == 0)
			tobinary(nbr);
	}
}

int		main(void)
{
	ft_putnbr_base(100, "0123456789ABCDEF");
	putchar('\n');
	ft_putnbr_base(9, "0123456789");
	putchar('\n');
	ft_putnbr_base(100, "poneyvif");
	putchar('\n');
	ft_putnbr_base(100, "01");
	putchar('\n');
}
