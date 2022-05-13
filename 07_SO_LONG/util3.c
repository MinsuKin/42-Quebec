/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:15:51 by minkim            #+#    #+#             */
/*   Updated: 2022/05/13 15:52:00 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_putx(unsigned int ud)
{
	int	res;

	res = 0;
	if (ud / 16)
		res += ft_putx(ud / 16);
	if ((ud % 16) >= 10)
		res += ft_putchar((ud % 16) - 10 + 'a');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int	ft_putxx(unsigned int ud)
{
	int	res;

	res = 0;
	if (ud / 16)
		res += ft_putxx(ud / 16);
	if ((ud % 16) >= 10)
		res += ft_putchar((ud % 16) - 10 + 'A');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int	ft_put_x(t_args *args, va_list ap)
{
	int	d;

	d = va_arg(ap, int);
	if (args->c == 'x')
		return (ft_putx(d));
	else if (args->c == 'X')
		return (ft_putxx(d));
	return (0);
}

int	ft_putp(unsigned long ul)
{
	int	res;

	res = 0;
	if (ul / 16)
		res += ft_putp(ul / 16);
	if ((ul % 16) >= 10)
		res += ft_putchar((ul % 16) - 10 + 'a');
	else
		res += ft_putchar((ul % 16) + '0');
	return (res);
}

int	ft_put_p(va_list ap)
{
	ft_putstr("0x");
	return (2 + ft_putp((unsigned long)va_arg(ap, void *)));
}
