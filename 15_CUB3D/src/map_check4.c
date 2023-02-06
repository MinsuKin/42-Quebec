/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:05:29 by minkim            #+#    #+#             */
/*   Updated: 2023/02/02 13:09:30 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_right_upndown(int i, int j)
{
	t_data	*data;

	data = get_data();
	while (data->map_file[i + 1])
	{
		if (data->map_file[i][j] == '1' && data->map_file[i + 1][j] == '1')
			;
		else if (data->map_file[i][j] == '1' && data->map_file[i + 1][j] == '0')
			exit_error("invalid map ");
		else if (data->map_file[i][j] == '1' && data->map_file[i + 1][j] == ' ')
		{
			if (data->map_file[i][j - 1] != '1')
				exit_error("invalid map ");
		}
		i++;
	}
	return (1);
}

int	check_left_upndown(int i, int j)
{
	t_data	*data;

	data = get_data();
	while (data->map_file[i + 1])
	{
		j = 0;
		while (data->map_file[i][j] == ' ')
			j++;
		if (data->map_file[i][j] == '1' && data->map_file[i + 1][j] == '1')
			;
		else if (data->map_file[i][j] == '1' && data->map_file[i + 1][j] == '0')
			exit_error("invalid map ");
		else if (data->map_file[i][j] == '1' && data->map_file[i + 1][j] == ' ')
		{
			if (data->map_file[i][j + 1] != '1')
				exit_error("invalid map ");
		}
		i++;
	}
	return (1);
}
