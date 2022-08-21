/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:15:36 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/09 10:25:53 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	dispatch(va_list *ap, char type, int *bytes, int fd)
{
	if (type == 'c')
		putchar_fd(va_arg(*ap, int), fd, bytes);
	if (type == 'd')
		putnbr_fd(va_arg(*ap, int), fd, bytes);
	if (type == 's')
		putstr_fd(va_arg(*ap, char *), fd, bytes);
	if (type == 'u')
		putunbr_fd(va_arg(*ap, unsigned int), fd, bytes);
	if (type == 'i')
		putnbr_fd(va_arg(*ap, int), fd, bytes);
	if (type == 'x')
		puthexa_fd(va_arg(*ap, int), 'x', fd, bytes);
	if (type == 'X')
		puthexa_fd(va_arg(*ap, int), 'X', fd, bytes);
	if (type == 'p')
		putaddr_fd(va_arg(*ap, long), 0, fd, bytes);
	if (type == '%')
		putchar_fd('%', fd, bytes);
	return ;
}

// add a character count variable.
int	ft_printf(int fd, const char *string, ...)
{
	va_list	ap;
	int		bytes;

	bytes = 0;
	va_start(ap, string);
	while (*string)
	{
		if (*string != '%')
			putchar_fd(*string, fd, &bytes);
		else
		{
			string++;
			dispatch(&ap, *string, &bytes, fd);
		}
		string++;
	}
	va_end(ap);
	return (bytes);
}
