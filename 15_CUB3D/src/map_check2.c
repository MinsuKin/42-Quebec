/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:34:13 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 15:38:00 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//
int	check_surround_first_zero(int i, int j)
{
	t_data	*data;

	data = get_data();
	if (i < 1 || j < 1)
		exit_error("invalid map ");
	if (data->map_file[i][j - 1] == ' ')
		exit_error("invalid map ");
	if (data->map_file[i - 1][j - 1] == '1' && \
		data->map_file[i - 1][j] == '1' && data->map_file[i][j - 1] == '1')
		return (0);
	else
		exit_error("invalid map ");
	return (1);
}

//
int	check_closed_first_zero(void)
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
			if (data->map_file[i][j] == '0')
			{
				if (check_surround_first_zero(i, j))
					return (0);
				return (flood_fill_first_zero(i, j));
			}
			j++;
		}
		i++;
	}
	return (0);
}

//
void	check_surround_last_row(int i, int j)
{
	t_data	*data;

	data = get_data();
	if (data->map_file[i - 1][j] != '1')
	{
		if (data->map_file[i][j + 1] && data->map_file[i][j + 1] != '1')
			exit_error("invalid map ");
	}
}

//
int	check_last_row(void)
{
	t_data	*d;
	int		i;
	int		flag;

	d = get_data();
	flag = 0;
	i = 0;
	while (d->map_file[d->height - 1][i])
	{
		if (ft_strchr("1 ", d->map_file[d->height - 1][i]) == NULL)
			exit_error("invalid map ");
		if (flag == 0 && d->map_file[d->height - 1][i] == '1')
		{
			check_surround_last_row(d->height - 1, i);
			flag = 1;
		}
		i++;
	}
	return (0);
}
