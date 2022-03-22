/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:13:04 by minkim            #+#    #+#             */
/*   Updated: 2022/01/30 15:03:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
