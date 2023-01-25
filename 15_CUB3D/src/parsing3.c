/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:39:41 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 15:51:40 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Just here for norm
void	set_texture(int *i, int side)
{
	t_data	*data;

	data = get_data();
	if (data->tex_path[side])
		exit_error("Too many texture paths in map file");
	data->tex_path[side] = strpop(ft_strdup(data->map_file[*i] + 3), -1);
	data->map_file = array_del_one(data->map_file, *i);
	--(*i);
}
