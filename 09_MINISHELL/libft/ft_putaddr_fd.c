/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:07:46 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/25 09:16:53 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// prefix == check if you should print '0x' or not.
void	ft_putaddr_fd(long n, int prefix, int fd)
{
	char			*base;
	long long		num;

	if (fd < 0)
		return ;
	if (prefix == 0)
		ft_putstr_fd("0x", 1);
	prefix = 1;
	base = "0123456789abcdef";
	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	if (num >= 16)
		ft_putaddr_fd(num / 16, prefix, fd);
	ft_putchar_fd(base[num % 16], fd);
}
