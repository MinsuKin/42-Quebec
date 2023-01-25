/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:06 by chughes           #+#    #+#             */
/*   Updated: 2023/01/17 13:28:55 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Cleans up and exits program
int	exit_window(int keycode, t_data **data)
{
	keycode = 0;
	if (*data)
		del_data();
	exit(0);
}

// Closes window, cleans up, and exits
void	close_window(t_data **data)
{
	mlx_destroy_window((*data)->mlx, (*data)->win);
	del_data();
	exit(0);
}

// Checks key presses
int	keydown(int keycode, t_data **data)
{
	if (keycode == ESC_KEY)
		close_window(data);
	if (keycode == W_KEY)
		move_north(data);
	if (keycode == A_KEY)
		move_west(data);
	if (keycode == S_KEY)
		move_south(data);
	if (keycode == D_KEY)
		move_east(data);
	if (keycode == L_KEY)
		look_left(data);
	if (keycode == R_KEY)
		look_right(data);
	return (0);
}
