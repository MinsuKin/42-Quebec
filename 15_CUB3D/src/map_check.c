/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:47:02 by minkim            #+#    #+#             */
/*   Updated: 2023/02/02 15:43:05 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Check if there is only one player point
int	check_player(void)
{
	t_data	*data;
	int		i;
	int		j;
	int		flag;

	data = get_data();
	flag = 0;
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (ft_strchr("NESW", data->map_file[i][j]) != NULL)
				flag++;
			j++;
		}
		i++;
	}
	if (flag != 1)
		return (1);
	return (0);
}

// Check if there is a character which is not allowed
int	check_space(void)
{
	t_data	*data;
	int		i;
	int		j;
	int		flag1;

	data = get_data();
	i = 0;
	flag1 = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (ft_strchr("\n01 NESW", data->map_file[i][j]) == NULL)
				return (1);
			if (data->map_file[i][j] == '1')
				flag1++;
			j++;
		}
		i++;
	}
	if (flag1 < 8)
		return (1);
	return (0);
}

//
int	flood_fill_player(int x, int y)
{
	t_data	*data;

	data = get_data();
	if (x >= data->height || y >= (int)ft_strlen(data->map_file[x]))
		exit_error("invalid map ");
	if (data->map_file[x][y] == '0')
	{
		data->map_file[x][y] = '=';
		flood_fill_player(x + 1, y);
		flood_fill_player(x, y + 1);
		flood_fill_player(x - 1, y);
		flood_fill_player(x, y - 1);
	}
	return (0);
}

// Check if the map is properly closed
int	check_closed_player(void)
{
	t_data	*data;

	data = get_data();
	data->map_file[(int)data->pos[X]][(int)data->pos[Y]] = '0';
	return (flood_fill_player(data->pos[X], data->pos[Y]));
}

//
int	flood_fill_first_zero(int x, int y)
{
	t_data	*data;

	data = get_data();
	if (x >= data->height || y >= (int)ft_strlen(data->map_file[x])
		|| data->map_file[x][y] == ' ')
		exit_error("invalid map ");
	if (data->map_file[x][y] == '0')
	{
		data->map_file[x][y] = '=';
		flood_fill_first_zero(x + 1, y);
		flood_fill_first_zero(x, y + 1);
		flood_fill_first_zero(x - 1, y);
		flood_fill_first_zero(x, y - 1);
	}
	return (0);
}
