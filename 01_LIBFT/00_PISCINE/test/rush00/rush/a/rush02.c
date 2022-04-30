/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:17:56 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/02/14 12:53:11 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (column == 1 || column == max_columns)
			{
				if (line == 1)
					ft_putchar('A');
				else if (line == max_rows)
					ft_putchar('C');
				else
					ft_putchar('B');
			}
			else if (line == 1 || line == max_rows)
				ft_putchar('B');
			else
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
