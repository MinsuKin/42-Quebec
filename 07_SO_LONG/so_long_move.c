/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:43:15 by minkim            #+#    #+#             */
/*   Updated: 2022/05/14 17:06:01 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_check(t_param *param, int y, int x)
{
	if (param->two_d_map[y][x] == '0')
		return (1);
	if (param->two_d_map[y][x] == 'P')
		return (1);
	if (param->two_d_map[y][x] == 'C')
	{
		param->collected++;
		param->two_d_map[y][x] = '0';
		mlx_put_image_to_window(param->mlx, param->win, param->tile, \
		x * 64, y * 64);
		return (1);
	}
	if (param->two_d_map[y][x] == 'E' && param->collected == param->collect_cnt)
	{
		ft_printf("You finished the game in %d steps\n", param->cnt);
		exit(0);
	}
	return (0);
}

void	move_w(t_param *param)
{
	if (move_check(param, param->y - 1, param->x))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, \
		param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, \
		param->x * 64, (param->y - 1) * 64);
		param->y--;
		ft_printf("Movement count: %d\n", ++param->cnt);
	}
}

void	move_s(t_param *param)
{
	if (move_check(param, param->y + 1, param->x))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, \
		param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, \
		param->x * 64, (param->y + 1) * 64);
		param->y++;
		ft_printf("Movement count: %d\n", ++param->cnt);
	}
}

void	move_a(t_param *param)
{
	if (move_check(param, param->y, param->x - 1))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, \
		param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, \
		(param->x - 1) * 64, param->y * 64);
		param->x--;
		ft_printf("Movement count: %d\n", ++param->cnt);
	}
}

void	move_d(t_param *param)
{
	if (move_check(param, param->y, param->x + 1))
	{	
		mlx_put_image_to_window(param->mlx, param->win, param->tile, \
		param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, \
		(param->x + 1) * 64, param->y * 64);
		param->x++;
		ft_printf("Movement count: %d\n", ++param->cnt);
	}
}
