/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:40:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/02/13 12:28:42 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void 	ft_putchar (char c)
{
	write(1, &c, 1);
}	

void rush(int width, int length)
{
	unsigned int 	l;
	unsigned int 	w;

	l = 1;
	while (l <= length)
	{
		w = 1;
		while( w <= width)
		{
			if (( w == 1 && l == 1) || (w == width && l == length))
				ft_putchar('/');
			else if (( w == width && l == 1) || (w == 1 && l == length))
				ft_putchar('\\');
			else if (( w > 1 && w < width) && ( l == 1 || l == length ))
				ft_putchar('*');
			else if (( l > 1 && l < length) && ( w == 1 || w == width))
				ft_putchar('*');
			else 
				ft_putchar(' ');
			w++;
		}
		ft_putchar('\n');
		l++;
	}
}
int main()
{
	rush(5,3);
	ft_putchar('\n');
	ft_putchar('\n');


	rush(5,1);
	ft_putchar('\n');
	ft_putchar('\n');

	
	rush(1,1);
	ft_putchar('\n');
	ft_putchar('\n');
	

	rush(1,5);
	ft_putchar('\n');
	ft_putchar('\n');


	rush(4,4);
	ft_putchar('\n');
	ft_putchar('\n');

	return 0;
}









