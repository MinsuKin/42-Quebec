/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:14:26 by minkim            #+#    #+#             */
/*   Updated: 2022/01/30 15:03:11 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_putp(unsigned long ul)
{
	int res;

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
