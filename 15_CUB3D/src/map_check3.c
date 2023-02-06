/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:37:20 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 15:23:07 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//
int	check_surround_first_one(int i, int j)
{
	t_data	*data;

	data = get_data();
	if (data->map_file[i +1][j] != '1' || data->map_file[i][j -1] != '1')
		exit_error("invalid map ");
	return (0);
}

//
int	check_first_row(void)
{
	t_data	*data;
	int		i;

	data = get_data();
	i = 0;
	while (data->map_file[0][i])
	{
		if (ft_strchr("1 ", data->map_file[0][i]) == NULL)
			exit_error("invalid map ");
		i++;
	}
	return (0);
}

//
int	check_left(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			while (data->map_file[i][j] == ' ')
				j++;
			if (data->map_file[i][j] == '1' && check_left_upndown(i, j))
				return (0);
			else
				exit_error("invalid map ");
			j++;
		}
		i++;
	}
	return (0);
}

//
int	check_right(void)
{
	t_data	*data;
	int		i;
	int		j;

	data = get_data();
	i = 0;
	while (data->map_file[i])
	{
		j = 0;
		while (data->map_file[i][j])
		{
			if (data->map_file[i][j] == '\n')
			{
				while (data->map_file[i][--j] == ' ')
					;
				if (data->map_file[i][j] == '1' && check_right_upndown(i, j))
					break ;
				else
					exit_error("invalid map ");
			}
			j++;
		}
		i++;
	}
	return (0);
}

// Check if the map is valid
void	check_map(void)
{
	t_data	*data;

	data = get_data();
	if (check_first_row())
		exit_error("invalid map ");
	if (check_last_row())
		exit_error("invalid map ");
	if (check_left())
		exit_error("invalid map ");
	if (check_right())
		exit_error("invalid map ");
	if (check_player())
		exit_error("invalid map ");
	if (check_space())
		exit_error("invalid map ");
	if (check_closed_player())
		exit_error("invalid map ");
	if (check_closed_first_zero())
		exit_error("invalid map ");
	return ;
}
