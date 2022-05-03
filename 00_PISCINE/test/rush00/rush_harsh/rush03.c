/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:06:33 by minkim            #+#    #+#             */
/*   Updated: 2021/02/13 16:12:59 by minkim           ###   ########.fr       */
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
			if (( w == 1 && l == 1) || (w == 1 && l == length))
				ft_putchar('A');
			else if (( w == width && l == 1) || (w == width && l == length))
				ft_putchar('C');
			else if (( w > 1 && w < width) && ( l == 1 || l == length ))
				ft_putchar('B');
			else if (( l > 1 && l < length) && ( w == 1 || w == width))
				ft_putchar('B');
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









