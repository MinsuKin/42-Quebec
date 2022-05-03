/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:18:33 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/02/16 09:28:20 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar();

void	rush(int max_columns, int max_rows)
{
	int		line;
	int		column;

	line = 0;
	while (++line <= max_rows && (max_columns > 0 && max_rows > 0))
	{
		column = 0;
		while (++column <= max_columns)
		{
			if (line == 1 || line == max_rows)
			{
				if (column == 1)
					ft_putchar('A');
				else if (column == max_columns)
					ft_putchar('C');
				else
					ft_putchar('B');
			}
			else if (column == 1 || column == max_columns)
				ft_putchar('B');
			else
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
