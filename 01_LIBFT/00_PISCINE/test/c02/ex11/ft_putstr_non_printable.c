/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:38:52 by minkim            #+#    #+#             */
/*   Updated: 2021/02/19 12:33:23 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void change_to_hex(unsigned char c)
{
	char *base;
	base = "0123456789abcdef";
	ft_putchar(base[c / 16]);
	ft_putchar(base[c % 16]);
}

void	ft_putstr_non_printable(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= ' ' && str[i] <= '~'))
		{
			ft_putchar('\\');
			change_to_hex(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
}

int		main(void)
{
	char text1[] = "\nCou	cou\ntu va	s bien ?\n";
	ft_putstr_non_printable(text1);
	return (0);
}
