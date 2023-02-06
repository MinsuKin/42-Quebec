/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:29:23 by chughes           #+#    #+#             */
/*   Updated: 2023/01/30 12:47:51 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Reads map file into an array of strings
void	read_map(char *map_name)
{
	t_data	*d;
	char	*line;
	int		map_fd;

	d = get_data();
	map_fd = open(map_name, O_RDONLY);
	if (map_fd == -1)
		exit_error("could not open map file");
	line = gnl(map_fd);
	while (line)
	{
		d->map_file = array_realloc(d->map_file, arraylen(d->map_file) + 1);
		d->map_file[arraylen(d->map_file)] = line;
		line = gnl(map_fd);
	}
	close(map_fd);
	return ;
}

// Parses map_file into textures, colours, and int array
void	parse_map(void)
{
	t_data	*data;

	data = get_data();
	grab_textures();
	grab_colors();
	grab_map();
	return ;
}

// Removes texture lines from map_file
void	grab_textures(void)
{
	t_data	*d;
	int		i;

	d = get_data();
	i = 0;
	while (d->map_file && d->map_file[i])
	{
		if (ft_strncmp(d->map_file[i], "NO ", 3) == 0)
			set_texture(&i, NORTH);
		else if (ft_strncmp(d->map_file[i], "SO ", 3) == 0)
			set_texture(&i, SOUTH);
		else if (ft_strncmp(d->map_file[i], "WE ", 3) == 0)
			set_texture(&i, WEST);
		else if (ft_strncmp(d->map_file[i], "EA ", 3) == 0)
			set_texture(&i, EAST);
		++i;
	}
	if (!d->tex_path[NORTH] || !d->tex_path[EAST] || !d->tex_path[SOUTH]
		|| !d->tex_path[WEST])
		exit_error("with map file");
}

// Removed color lines from map_file
void	grab_colors(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		if (ft_strncmp(data->map_file[i], "F ", 2) == 0
			&& data->floor_name == NULL)
		{
			data->floor_name = strpop(ft_strdup(data->map_file[i] + 2), -1);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		if (ft_strncmp(data->map_file[i], "C ", 2) == 0
			&& data->ceiling_name == NULL)
		{
			data->ceiling_name = strpop(ft_strdup(data->map_file[i] + 2), -1);
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		++i;
	}
	set_colors();
}

// Sets floor and ceiling colors
void	set_colors(void)
{
	t_data	*data;
	char	**floor;
	char	**ceiling;

	data = get_data();
	if (!data->floor_name || !data->ceiling_name)
		exit_error("with map file");
	floor = ft_split(data->floor_name, ',');
	ceiling = ft_split(data->ceiling_name, ',');
	if (arraylen(floor) != 3 || arraylen(ceiling) != 3)
		exit_error("with colors");
	data->floor = ft_atoi(floor[0]) << 16 | ft_atoi(floor[1]) << 8 \
	| ft_atoi(floor[2]);
	data->ceiling = ft_atoi(ceiling[0]) << 16 | ft_atoi(ceiling[1]) << 8 \
	| ft_atoi(ceiling[2]);
	check_numbers(floor, ceiling);
	floor = free_array(floor);
	ceiling = free_array(ceiling);
}
