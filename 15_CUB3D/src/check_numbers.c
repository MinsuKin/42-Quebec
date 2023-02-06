/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:59 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 16:28:02 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Checks if all digits are all numeric
static bool	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
			return (true);
		++i;
	}
	return (false);
}

// Checks that numbers are within 0-255
void	check_numbers(char **floor, char **ceil)
{
	bool	flag;

	flag = false;
	if (ft_isdigit(floor[0]) || ft_isdigit(floor[1]) || ft_isdigit(floor[2])
		|| ft_isdigit(ceil[0]) || ft_isdigit(ceil[0]) || ft_isdigit(ceil[0]))
		flag = true;
	if (ft_atoi(floor[0]) > 255 || ft_atoi(floor[0]) < 0
		|| ft_atoi(floor[1]) > 255 || ft_atoi(floor[1]) < 0
		|| ft_atoi(floor[2]) > 255 || ft_atoi(floor[2]) < 0
		|| ft_atoi(ceil[0]) > 255 || ft_atoi(ceil[0]) < 0
		|| ft_atoi(ceil[1]) > 255 || ft_atoi(ceil[1]) < 0
		|| ft_atoi(ceil[2]) > 255 || ft_atoi(ceil[2]) < 0)
		flag = true;
	if (flag)
	{
		free_array(floor);
		free_array(ceil);
		exit_error("with colors");
	}
}
