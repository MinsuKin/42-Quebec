/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:03:23 by minkim            #+#    #+#             */
/*   Updated: 2022/05/13 15:51:57 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_puti(int d)
{
	int	res;

	res = 0;
	if (d == -2147483648)
	{
		res += ft_putchar('-');
		res += ft_putstr("2147483648");
		return (res);
	}
	if (d < 0)
	{
		res += ft_putchar('-');
		d *= -1;
	}
	if (d / 10)
		res += ft_puti(d / 10);
	res += ft_putchar((d % 10) + '0');
	return (res);
}

int	ft_put_d(va_list ap)
{
	int	d;

	d = va_arg(ap, int);
	return (ft_puti(d));
}

int	ft_putu(unsigned int u)
{
	int	res;

	res = 0;
	if (u / 10)
		res += ft_putu(u / 10);
	res += ft_putchar((u % 10) + '0');
	return (res);
}

int	ft_put_u(va_list ap)
{
	int	u;

	u = va_arg(ap, int);
	return (ft_putu(u));
}
