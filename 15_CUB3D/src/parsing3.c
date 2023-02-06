/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:39:41 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 13:10:16 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Just here for norm
void	set_texture(int *i, int side)
{
	t_data	*data;
	int		index;

	data = get_data();
	if (data->tex_path[side])
		exit_error("too many texture paths in map file");
	data->tex_path[side] = strpop(ft_strdup(data->map_file[*i] + 3), -1);
	index = 0;
	while (data->tex_path[side][0] == ' ')
		data->tex_path[side] = strpop(data->tex_path[side], 0);
	data->map_file = array_del_one(data->map_file, *i);
	--(*i);
}

int	check_division_space(int i, int j)
{
	t_data	*data;

	data = get_data();
	while (data->map_file[i][j] == ' ')
		j++;
	if (data->map_file[i][j] == '\n')
		exit_error("multiple maps detected");
	return (1);
}

int	check_division(int i, int j)
{
	t_data	*data;

	data = get_data();
	while (data->map_file[i][0] == '\n')
		i++;
	while (data->map_file[i] && ft_strchr("1 ", data->map_file[i][0]) != NULL)
	{
		if (data->map_file[i][j] == ' ')
			check_division_space(i, j);
		i++;
	}
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (data->map_file[i][j] == '\n' || data->map_file[i][j] == ' ')
				;
			else
				exit_error("invalid map");
			j++;
		}
		i++;
	}
	return (0);
}
