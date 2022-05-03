/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:16:43 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/02/15 09:06:57 by minkim           ###   ########.fr       */
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
			if (line == 1 || line == max_rows)
			{
				if (column == 1 || column == max_columns)
					ft_putchar('o');
				else
					ft_putchar('-');
			}
			else if (column == 1 || column == max_columns)
				ft_putchar('|');
			else
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
