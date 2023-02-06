/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:32:43 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 14:43:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	*d;

	d = get_data();
	init_data(argc, argv);
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "cub3D");
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_size, &d->endian);
	mlx_hook(d->win, ON_DESTROY, 0, exit_window, &d);
	mlx_hook(d->win, ON_KEYDOWN, 0, keydown, &d);
	mlx_loop_hook(d->mlx, render_frame, NULL);
	mlx_loop(d->mlx);
	exit(0);
}
