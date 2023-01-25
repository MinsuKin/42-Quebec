/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:31:06 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 15:50:18 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Loads xpm texture into a string of ints
void	load_texture(t_data *data, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	img.img = mlx_xpm_file_to_image(data->mlx, path, &img.width, &img.height);
	if (img.img == NULL)
		exit_error("could not load texture");
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_size, &img.endian);
	y = -1;
	while (++y < img.height)
	{
		x = -1;
		while (++x < img.width)
			texture[img.width * y + x] = ((int *)img.addr)[img.width * y + x];
	}
	mlx_destroy_image(data->mlx, img.img);
}

// Loads N, E, S, W textures into int*
void	load_textures(t_data *data)
{
	load_texture(data, data->tex[NORTH], data->tex_path[NORTH]);
	load_texture(data, data->tex[EAST], data->tex_path[EAST]);
	load_texture(data, data->tex[SOUTH], data->tex_path[SOUTH]);
	load_texture(data, data->tex[WEST], data->tex_path[WEST]);
}
