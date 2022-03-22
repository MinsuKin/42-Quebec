/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush04.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:19:01 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/02/14 14:03:20 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	output(int line, int column, int max_columns, int max_rows)
{
	if (column == 1 && line == 1)
		ft_putchar('A');
	else if ((column == 1 && line == max_rows) ||
		(column == max_columns && line == 1))
		ft_putchar('C');
	else
		ft_putchar('A');
}

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
			if ((column == 1 || column == max_columns) &&
					(line == 1 || line == max_rows))
				output(line, column, max_columns, max_rows);
			else if (column == 1 || column == max_columns ||
					line == 1 || line == max_rows)
				ft_putchar('B');
			else
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
