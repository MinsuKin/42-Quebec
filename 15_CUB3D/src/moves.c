/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:38 by chughes           #+#    #+#             */
/*   Updated: 2023/01/24 12:14:37 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Move player sprite north
void	move_north(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] + d->dir[X] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] += d->dir[X] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] + d->dir[Y] * MOVE_SPEED)])
		d->pos[Y] += d->dir[Y] * MOVE_SPEED;
	return ;
}

// Move player sprite east
void	move_east(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] + d->dir[Y] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] += d->dir[Y] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] - d->dir[X] * MOVE_SPEED)])
		d->pos[Y] -= d->dir[X] * MOVE_SPEED;
	return ;
}

// Move player sprite south
void	move_south(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] - d->dir[X] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] -= d->dir[X] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] - d->dir[Y] * MOVE_SPEED)])
		d->pos[Y] -= d->dir[Y] * MOVE_SPEED;
	return ;
}

// Move player sprite west
void	move_west(t_data **data)
{
	t_data	*d;

	d = (*data);
	if (!d->map[(int)(d->pos[X] - d->dir[Y] * MOVE_SPEED)][(int)(d->pos[Y])])
		d->pos[X] -= d->dir[Y] * MOVE_SPEED;
	if (!d->map[(int)(d->pos[X])][(int)(d->pos[Y] + d->dir[X] * MOVE_SPEED)])
		d->pos[Y] += d->dir[X] * MOVE_SPEED;
	return ;
}
