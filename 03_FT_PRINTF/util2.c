/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:03:23 by minkim            #+#    #+#             */
/*   Updated: 2022/01/30 15:54:09 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		if (ft_strchr("cspdiuxX%", *itr))
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
		return ft_put_s(ap);
	else if (args->c == 'c')
		return ft_put_c(ap);
	else if (args->c == 'd' || args->c == 'i')
		return ft_put_d(ap);
	else if (args->c == 'x' || args->c == 'X')
		return ft_put_x(args, ap);
	else if (args->c == 'p')
		return ft_put_p(ap);
	else if (args->c == 'u')
		return ft_put_u(ap);
	else if (args->c == '%')
    {
        ft_putchar('%');
		return (1);
    }
	return (0);
}
