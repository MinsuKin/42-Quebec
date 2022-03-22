/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:15:51 by minkim            #+#    #+#             */
/*   Updated: 2022/01/30 15:03:13 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_putx(unsigned int ud)
{
	int res;

	res = 0;
	if (ud / 16)
		res += ft_putx(ud / 16);
	if ((ud % 16) >= 10)
		res += ft_putchar((ud % 16) - 10 + 'a');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int ft_putxx(unsigned int ud)
{
	int res;

	res = 0;
	if (ud / 16)
		res += ft_putxx(ud / 16);
	if ((ud % 16) >= 10)
		res += ft_putchar((ud % 16) - 10 + 'A');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int ft_put_x(t_args *args, va_list ap)
{
	int	d;

	d = va_arg(ap, int);
	if (args->c == 'x')
		return (ft_putx(d));
	else if (args->c == 'X')
		return (ft_putxx(d));
	return (0);
}
