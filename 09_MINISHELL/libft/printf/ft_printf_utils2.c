/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:42:54 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/09 10:30:50 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	putunbr_fd(int n, int fd, int *bytes)
{
	int	num;

	num = n;
	if (num < 0)
	{
		putchar_fd('-', fd, bytes);
		num = -num;
	}
	if (num > 9)
	{
		putunbr_fd(num / 10, fd, bytes);
		putunbr_fd(num % 10, fd, bytes);
	}
	else
		putchar_fd(num + '0', fd, bytes);
	return ;
}
