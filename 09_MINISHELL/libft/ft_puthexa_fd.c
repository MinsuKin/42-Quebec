/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:18:33 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/25 09:17:11 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// flag == 'x', 'X' or 'p'. Specifies lowercase or uppercase for hexa base.
// p needs to print '0x' before the conversion.
void	ft_puthexa_fd(long n, char flag, int fd)
{
	char			*base;
	long long		num;

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
		ft_putchar_fd('-', fd);
		num = -num;
	}
	if (num >= 16)
		ft_puthexa_fd(num / 16, flag, fd);
	ft_putchar_fd(base[num % 16], fd);
}
