/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 10:51:46 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/09 10:30:37 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	putaddr_fd(long n, int prefix, int fd, int *bytes)
{
	char			*base;
	long long		num;

	if (fd < 0)
		return ;
	if (prefix == 0)
	{
		putstr_fd("0x", 1, bytes);
		prefix = 1;
	}
	base = "0123456789abcdef";
	num = n;
	if (num < 0)
	{
		putchar_fd('-', fd, bytes);
		num = -num;
	}
	if (num >= 16)
		putaddr_fd(num / 16, prefix, fd, bytes);
	putchar_fd(base[num % 16], fd, bytes);
	return ;
}

void	putchar_fd(char c, int fd, int *bytes)
{
	(*bytes)++;
	write(fd, &c, 1);
	return ;
}

void	puthexa_fd(long n, char flag, int fd, int *bytes)
{
	char	*base;
	int		num;

	if (fd < 0)
		return ;
	if (flag == 'x')
		base = "0123456789abcdef";
	else if (flag == 'X')
		base = "0123456789ABCDEF";
	else
		return ;
	num = n;
	if (num < 0)
	{
		putchar_fd('-', fd, bytes);
		num = -num;
	}
	if (num >= 16)
		puthexa_fd(num / 16, flag, fd, bytes);
	putchar_fd(base[num % 16], fd, bytes);
}

void	putstr_fd(char *s, int fd, int *bytes)
{
	int	i;

	i = 0;
	if (!s)
		putstr_fd("(null)", fd, bytes);
	else
	{
		while (s[i])
		{
			putchar_fd(s[i], fd, bytes);
			i++;
		}
	}
	return ;
}

void	putnbr_fd(int n, int fd, int *bytes)
{
	long	num;

	num = n;
	if (num < 0)
	{
		putchar_fd('-', fd, bytes);
		num = -num;
	}
	if (num > 9)
	{
		putnbr_fd(num / 10, fd, bytes);
		putnbr_fd(num % 10, fd, bytes);
	}
	else
		putchar_fd(num + '0', fd, bytes);
	return ;
}
