/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 13:28:23 by minkim            #+#    #+#             */
/*   Updated: 2021/02/13 16:20:44 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	rush(int x, int y)
{
	int width;
	int height;

	height = 1;
	while (height <= y)
	{
		width = 1;
		while (width <= x)
		{
			if ((width == 1 && height == 1) || (width == 1 && height == y))
				ft_putchar('A');
			else if ((width == x && height == 1) || (width == x && height == y))
				ft_putchar('C');
			else if ((width < x && width > 1) && (height == 1 || height == y))
				ft_putchar('B');
			else if ((height < y && height > 1) && (width == 1 || width == x))
				ft_putchar('B');
			else
				ft_putchar(' ');
			width++;
		}
		ft_putchar('\n');
		height++;
	}
}
