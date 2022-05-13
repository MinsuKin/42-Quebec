/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 15:02:59 by minkim            #+#    #+#             */
/*   Updated: 2022/05/13 15:53:50 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_args(t_args *args)
{
	args->c = 0;
	args->has_width = 0;
	args->has_precision = 0;
	args->width = 0;
	args->precision = 0;
}

char	*read_args(t_args *args, char *itr)
{
	if (!itr || *itr != '%')
		return (itr);
	itr++;
	while (*itr)
	{
		initialize_args(args);
		if (ft_strchrr("cspdiuxX%", *itr))
		{
			args->c = *itr;
			itr++;
			return (itr);
		}
		itr++;
	}
	return (itr);
}

int	ft_put_conv(t_args *args, va_list ap)
{
	if (args->c == 's')
		return (ft_put_s(ap));
	else if (args->c == 'c')
		return (ft_put_c(ap));
	else if (args->c == 'd' || args->c == 'i')
		return (ft_put_d(ap));
	else if (args->c == 'x' || args->c == 'X')
		return (ft_put_x(args, ap));
	else if (args->c == 'p')
		return (ft_put_p(ap));
	else if (args->c == 'u')
		return (ft_put_u(ap));
	else if (args->c == '%')
	{
		ft_putchar('%');
		return (1);
	}
	return (0);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_printf(const char *format, ...)
{
	char	*itr;
	int		res;
	t_args	args;
	va_list	ap;

	itr = (char *)format;
	if (!itr)
		return (0);
	res = 0;
	va_start(ap, format);
	while (*itr)
	{
		if (*itr == '%')
		{
			itr = read_args(&args, itr);
			res += ft_put_conv(&args, ap);
			continue ;
		}
		res += ft_putchar(*itr);
		itr++;
	}
	va_end(ap);
	return (res);
}
