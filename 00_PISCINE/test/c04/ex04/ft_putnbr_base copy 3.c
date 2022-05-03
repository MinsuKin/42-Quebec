/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:24:36 by minkim            #+#    #+#             */
/*   Updated: 2021/02/23 16:38:26 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	tooctal(int num, char *base)
{
	int i;

	while (base[i])
		i++;
	if (num < 0)
	{
		write(1, "-", 1);
		num = -num;
	}
	if (num > 0)
	{
		tooctal(num / i, base);
		write(1, &(base[num % i]), 1);
	}
}

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
	int	i;

	i = 0;
	while (base[i])
		i++;
	if (i > 1 && plusmi(base) == 1 && doublechar(base) == 1)
		tooctal(nbr, base);
}
