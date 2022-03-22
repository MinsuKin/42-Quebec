/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:03:56 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/04 08:15:47 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_header.h>

void	ft_set_mark(int maxsquare, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < maxsquare)
	{
		j = 0;
		while (j < maxsquare)
		{
			map->map[map->y_bsq + i][map->x_bsq + j] = map->fill;
			j++;
		}
		i++;
	}
}

void	ft_print_grid(t_map map)
{
	int i;
	int j;

	i = 1;
	while (i < map.row)
	{
		j = 0;
		while (j < map.col)
		{
			ft_putchar(map.map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i < map.row)
	{
		free(map.map[i]);
		i++;
	}
	free(map.map);
}

int		ft_check_square(int size, int x, int y, t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < size && x + i < map.col)
	{
		j = 0;
		while (j < size && y + j < map.row)
		{
			if (map.map[j + y][i + x] != map.empty)
				return (0);
			j++;
		}
		i++;
	}
	if (i == size && j == size)
		return (1);
	else
		return (0);
}

void	ft_is_valid(t_map *map, int x, int y, int *maxsquare)
{
	int	size;

	size = 1;
	while (ft_check_square(size, x, y, *map))
		size++;
	size--;
	if (size > *maxsquare)
	{
		*maxsquare = size;
		map->y_bsq = y;
		map->x_bsq = x;
	}
}

void	ft_do_square(t_map map)
{
	int x;
	int y;
	int	maxsquare;

	y = 1;
	map.x_bsq = 0;
	map.y_bsq = 0;
	maxsquare = 0;
	while (y + maxsquare < map.row)
	{
		x = 0;
		while (x + maxsquare < map.col)
		{
			ft_is_valid(&map, x, y, &maxsquare);
			x++;
		}
		y++;
	}
	ft_set_mark(maxsquare, &map);
	ft_print_grid(map);
}
