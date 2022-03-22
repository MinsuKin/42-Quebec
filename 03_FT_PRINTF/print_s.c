/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:11:43 by minkim            #+#    #+#             */
/*   Updated: 2022/01/30 15:03:11 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_s(va_list ap)
{
	int		len;
	char	*s;
	int 	res;
	int		i;

	s = va_arg(ap, char *);
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	res = 0;
	i = 0;
	while (s[i] && i < len)
	{
		res += ft_putchar(s[i]);
		i++;
	}
	return (res);
}
