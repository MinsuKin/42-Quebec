/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:03:23 by minkim            #+#    #+#             */
/*   Updated: 2022/05/13 15:44:25 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

int	ft_putstr(char *str)
{
	int	res;

	if (!str)
		return (0);
	res = 0;
	while (*str)
	{
		res += ft_putchar(*str);
		str++;
	}
	return (res);
}

int	ft_strlen(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

int	ft_put_c(va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	ft_putchar(c);
	return (1);
}

int	ft_put_s(va_list ap)
{
	int		len;
	char	*s;
	int		res;
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
