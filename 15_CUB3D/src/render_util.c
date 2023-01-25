/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:22:28 by chughes           #+#    #+#             */
/*   Updated: 2023/01/24 12:20:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Sets frame->ray_dir
void	ray_direction(t_data *data, t_frame *frame)
{
	frame->camera_x = 2 * frame->x / (double)WIDTH - 1;
	frame->ray_dir[X] = data->dir[X] + data->plane[X] * frame->camera_x;
	frame->ray_dir[Y] = data->dir[Y] + data->plane[Y] * frame->camera_x;
}

// Length of ray from one x or y-side to next x or y-side
void	ray_length(t_frame *frame)
{
	frame->delta_dst[X] = fabs(1 / frame->ray_dir[X]);
	frame->delta_dst[Y] = fabs(1 / frame->ray_dir[Y]);
}

// Evaluates distance to wall hit
void	side_distance(t_data *d, t_frame *f)
{
	if (f->ray_dir[X] < 0)
	{
		f->step[X] = -1;
		f->side_dst[X] = (d->pos[X] - f->map[X]) * f->delta_dst[X];
	}
	else
	{
		f->step[X] = 1;
		f->side_dst[X] = (f->map[X] + 1.0 - d->pos[X]) * f->delta_dst[X];
	}
	if (f->ray_dir[Y] < 0)
	{
		f->step[Y] = -1;
		f->side_dst[Y] = (d->pos[Y] - f->map[Y]) * f->delta_dst[Y];
	}
	else
	{
		f->step[Y] = 1;
		f->side_dst[Y] = (f->map[Y] + 1.0 - d->pos[Y]) * f->delta_dst[Y];
	}
}

// Extends ray until it finds a wall
void	check_hit(t_data *data, t_frame *frame)
{
	frame->hit = false;
	while (frame->hit == false)
	{
		if (frame->side_dst[X] < frame->side_dst[Y])
		{
			frame->side_dst[X] += frame->delta_dst[X];
			frame->map[X] += frame->step[X];
			if (frame->step[X] > 0)
				frame->side = NORTH;
			else
				frame->side = SOUTH;
		}
		else
		{
			frame->side_dst[Y] += frame->delta_dst[Y];
			frame->map[Y] += frame->step[Y];
			if (frame->step[Y] > 0)
				frame->side = WEST;
			else
				frame->side = EAST;
		}
		if (data->map[frame->map[X]][frame->map[Y]] > 0)
			frame->hit = true;
	}
}
