/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:25:09 by minkim            #+#    #+#             */
/*   Updated: 2022/05/14 17:39:23 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	cnt_collect(char *map)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (map[i])
	{
		if (map[i] == 'C')
			c++;
		i++;
	}
	return (c);
}

void	ft_update(t_param *param, int x, int y)
{
	mlx_put_image_to_window(param->mlx, param->win, param->tile, \
	x * 64, y * 64);
	if (param->two_d_map[y][x] == '1')
		mlx_put_image_to_window(param->mlx, param->win, param->wall, \
		x * 64, y * 64);
	else if (param->two_d_map[y][x] == 'C')
		mlx_put_image_to_window(param->mlx, param->win, param->collect, \
		x * 64, y * 64);
	else if (param->two_d_map[y][x] == 'E')
		mlx_put_image_to_window(param->mlx, param->win, param->exit, \
		x * 64, y * 64);
	else if (param->two_d_map[y][x] == 'P')
	{
		mlx_put_image_to_window(param->mlx, param->win, param->player, \
		x * 64, y * 64);
		param->x = x;
		param->y = y;
	}
}

void	ft_render(t_param *param, char *map)
{
	int	row;
	int	col;
	int	y;
	int	x;

	param->collect_cnt = cnt_collect(map);
	row = ft_strlen_n(map);
	col = ft_strlen(map) / row--;
	param->win = mlx_new_window(param->mlx, row * 64, col * 64, "so_long");
	y = 0;
	while (y < col)
	{
		x = 0;
		while (x < row)
		{
			ft_update(param, x, y);
			x++;
		}
		y++;
	}
}
