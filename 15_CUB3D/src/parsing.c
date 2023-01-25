/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:46 by chughes           #+#    #+#             */
/*   Updated: 2023/01/24 12:26:00 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Moves map tiles from map_file to map
void	grab_map(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = -1;
	while (data->map_file[++i])
	{
		if (data->map_file[i][0] == '\n')
		{
			data->map_file = array_del_one(data->map_file, i);
			--i;
		}
		else if (ft_strchr("1 ", data->map_file[i][0]) == NULL)
			exit_error("error reading map ");
	}
	get_size();
	data->map = xalloc(data->height + 1, sizeof(int *));
	i = -1;
	while (++i <= data->height)
		data->map[i] = xalloc(data->width + 1, sizeof(int));
	copy_map();
}

// Copies values from map_file to map
void	copy_map(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if (j >= ft_linelen(data->map_file[i])
				|| data->map_file[i][j] == ' ')
				data->map[i][j] = SPACE;
			else if (data->map_file[i][j] == '0')
				data->map[i][j] = EMPTY;
			else if (data->map_file[i][j] == '1')
				data->map[i][j] = WALL;
			else if (ft_strchr("NESW", data->map_file[i][j]) != NULL)
				init_player(data->map_file[i][j], i, j);
			++j;
		}
		++i;
	}
}

// Sets player direction and location
void	init_player(char direction, int x, int y)
{
	t_data	*data;

	data = get_data();
	data->pos[X] = x + 0.5;
	data->pos[Y] = y + 0.5;
	if (direction == 'N')
	{
		data->dir[X] = -1.0;
		data->plane[Y] = 0.66;
	}
	if (direction == 'E')
	{
		data->dir[Y] = 1.0;
		data->plane[X] = 0.66;
	}
	if (direction == 'S')
	{
		data->dir[X] = 1.0;
		data->plane[Y] = -0.66;
	}
	if (direction == 'W')
	{
		data->dir[Y] = -1.0;
		data->plane[X] = -0.66;
	}
}

// Gets height and width from map
void	get_size(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	data->height = arraylen(data->map_file);
	data->width = 0;
	i = 0;
	while (i < data->height)
	{
		if (ft_strlen(data->map_file[i]) > (size_t)data->width)
			data->width = ft_strlen(data->map_file[i]) - 1;
		++i;
	}
}

// Checks input and sets map_file height
void	check_input(int argc, char *p)
{
	t_data	*data;

	data = get_data();
	if (argc != 2)
		exit_error("no map path given ");
	if (ft_strlen(p) >= 4 && ft_strncmp(&p[ft_strlen(p) - 4], ".cub", 4))
		exit_error("map does not have correct file suffix ");
	return ;
}
