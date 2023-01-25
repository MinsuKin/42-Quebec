/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:55 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 16:30:25 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Sets line height of current wall in view
void	get_line_height(t_data *data, t_frame *frame)
{
	double	temp[2];

	temp[X] = (frame->map[X] - data->pos[X] + (1 - frame->step[X]) / 2);
	temp[Y] = (frame->map[Y] - data->pos[Y] + (1 - frame->step[Y]) / 2);
	if (frame->side == NORTH || frame->side == SOUTH)
		frame->perp_dst = temp[X] / frame->ray_dir[X];
	if (frame->side == EAST || frame->side == WEST)
		frame->perp_dst = temp[Y] / frame->ray_dir[Y];
	frame->line_height = (int)(HEIGHT / frame->perp_dst);
}

// Finds x value of ray cast on a wall
void	wall_texture_x(t_data *data, t_frame *frame)
{
	if (frame->side == NORTH || frame->side == SOUTH)
		frame->wall_x = data->pos[Y] + frame->perp_dst * frame->ray_dir[Y];
	if (frame->side == EAST || frame->side == WEST)
		frame->wall_x = data->pos[X] + frame->perp_dst * frame->ray_dir[X];
	frame->wall_x -= floor(frame->wall_x);
}

// Gets line height of texture to draw
void	draw_length(t_frame *frame)
{
	frame->draw_start = -frame->line_height / 2 + HEIGHT / 2;
	frame->draw_end = frame->line_height / 2 + HEIGHT / 2;
	if (frame->draw_start < 0)
		frame->draw_start = 0;
	if (frame->draw_end >= HEIGHT)
		frame->draw_end = HEIGHT - 1;
}

// Draws full vertical line to data->img
void	draw_line(t_data *data, t_frame *f)
{
	int		pixel;
	int		color;
	double	tex_step;
	double	tex_pos;

	wall_texture_x(data, f);
	f->tex[X] = f->wall_x * TEX_WIDTH;
	if (((f->side == NORTH || f->side == SOUTH) && f->ray_dir[X] > 0)
		|| ((f->side == EAST || f->side == WEST) && f->ray_dir[Y] < 0))
		f->tex[X] = TEX_WIDTH - f->tex[X] - 1;
	draw_length(f);
	pixel = -1;
	while (++pixel < f->draw_start)
		mlx_pixel_img(f->x, pixel, data->ceiling);
	tex_step = 1.0 * TEX_HEIGHT / f->line_height;
	tex_pos = (f->draw_start - HEIGHT / 2 + f->line_height / 2) * tex_step;
	while (++pixel < f->draw_end)
	{
		f->tex[Y] = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += tex_step;
		color = data->tex[f->side][TEX_HEIGHT * f->tex[Y] + f->tex[X]];
		mlx_pixel_img(f->x, pixel, color);
	}
	while (++pixel < HEIGHT)
		mlx_pixel_img(f->x, pixel, data->floor);
}

// Renders next frame from map to window
int	render_frame(void)
{
	t_data	*data;
	t_frame	*frame;

	data = get_data();
	frame = xalloc(1, sizeof(t_frame));
	while (frame->x < WIDTH)
	{
		ray_direction(data, frame);
		frame->map[X] = (int)data->pos[X];
		frame->map[Y] = (int)data->pos[Y];
		ray_length(frame);
		side_distance(data, frame);
		check_hit(data, frame);
		get_line_height(data, frame);
		draw_line(data, frame);
		frame->x++;
	}
	frame = xfree(frame);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
