/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:14:11 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 15:14:52 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Turns the camera left
void	look_left(t_data **data)
{
	t_data	*d;
	double	old_dir_x;
	double	old_plane_x;

	d = (*data);
	old_dir_x = d->dir[X];
	d->dir[X] = d->dir[X] * cos(ROT_SPEED) - d->dir[Y] * sin(ROT_SPEED);
	d->dir[Y] = old_dir_x * sin(ROT_SPEED) + d->dir[Y] * cos(ROT_SPEED);
	old_plane_x = d->plane[X];
	d->plane[X] = d->plane[X] * cos(ROT_SPEED) - d->plane[Y] * sin(ROT_SPEED);
	d->plane[Y] = old_plane_x * sin(ROT_SPEED) + d->plane[Y] * cos(ROT_SPEED);
}

// Turns the camera right
void	look_right(t_data **data)
{
	t_data	*d;
	double	old_dir_x;
	double	old_plane_x;

	d = (*data);
	old_dir_x = d->dir[X];
	d->dir[X] = d->dir[X] * cos(-ROT_SPEED) - d->dir[Y] * sin(-ROT_SPEED);
	d->dir[Y] = old_dir_x * sin(-ROT_SPEED) + d->dir[Y] * cos(-ROT_SPEED);
	old_plane_x = d->plane[X];
	d->plane[X] = d->plane[X] * cos(-ROT_SPEED) - d->plane[Y] * sin(-ROT_SPEED);
	d->plane[Y] = old_plane_x * sin(-ROT_SPEED) + d->plane[Y] * cos(-ROT_SPEED);
}
