/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:19 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 15:27:12 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Singleton itialization and reference getter
t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (data == NULL)
		data = xalloc(1, sizeof(t_data));
	return (data);
}

// Initialized data struct
void	init_data(int argc, char *argv[])
{
	t_data	*data;

	data = get_data();
	check_input(argc, argv[1]);
	read_map(argv[1]);
	parse_map();
	check_map();
	data->tex = xalloc(4, sizeof(int **));
	data->tex[NORTH] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->tex[EAST] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->tex[SOUTH] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->tex[WEST] = xalloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
	data->mlx = mlx_init();
	load_textures(data);
	return ;
}

// Frees maps
static void	free_map(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	if (data->map)
	{
		while (++i < data->height)
			data->map[i] = xfree(data->map[i]);
		data->map = xfree(data->map);
	}
	i = -1;
	if (data->map_file)
	{
		while (data->map_file[++i])
			data->map_file[i] = xfree(data->map_file[i]);
		data->map_file = xfree(data->map_file);
	}
}

// Frees textures
static void	free_textures(void)
{
	t_data	*data;

	data = get_data();
	if (data->tex)
	{
		if (data->tex[NORTH])
			data->tex[NORTH] = xfree(data->tex[NORTH]);
		if (data->tex[EAST])
			data->tex[EAST] = xfree(data->tex[EAST]);
		if (data->tex[SOUTH])
			data->tex[SOUTH] = xfree(data->tex[SOUTH]);
		if (data->tex[WEST])
			data->tex[WEST] = xfree(data->tex[WEST]);
		data->tex = xfree(data->tex);
	}
	if (data->tex_path[NORTH])
		data->tex_path[NORTH] = xfree(data->tex_path[NORTH]);
	if (data->tex_path[EAST])
		data->tex_path[EAST] = xfree(data->tex_path[EAST]);
	if (data->tex_path[SOUTH])
		data->tex_path[SOUTH] = xfree(data->tex_path[SOUTH]);
	if (data->tex_path[WEST])
		data->tex_path[WEST] = xfree(data->tex_path[WEST]);
}

// Frees data and its contents
void	del_data(void)
{
	t_data	*data;

	data = get_data();
	free_map();
	free_textures();
	if (data->floor_name)
		data->floor_name = xfree(data->floor_name);
	if (data->ceiling_name)
		data->ceiling_name = xfree(data->ceiling_name);
	data = xfree(data);
	return ;
}
