/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 08:46:50 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/04 08:47:23 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_header.h>

int		ft_check_first_2_lines(char **map)
{
	char	*buf;
	int		i;

	buf = map[0];
	while (*buf != 0)
		buf++;
	if (ft_strlen(map[0]) > 3 && *(buf - 1) >= ' ' && *(buf - 2) >= ' '
		&& *(buf - 3) >= ' ' && *(buf - 1) != *(buf - 2)
		&& *(buf - 1) != *(buf - 3) && *(buf - 2) != *(buf - 3))
	{
		i = 0;
		while (i < ((buf - 3) - map[0]))
		{
			if (map[0][i] < '0' || map[0][i] > '9')
				return (0);
			i++;
		}
		if (!map[1] || (map[1][0] != *(buf - 2)
			&& map[1][0] != *(buf - 3)))
			return (0);
		return (1);
	}
	else
		return (0);
}

int		ft_check_nb_lines(char **map, int row)
{
	char	*nblines;
	int		nblinesint;
	int		i;

	nblines = malloc(ft_strlen(map[0]) - 3);
	i = 0;
	while (i < ft_strlen(map[0]) - 3)
	{
		nblines[i] = map[0][i];
		i++;
	}
	nblines[i] = 0;
	nblinesint = ft_atoi(nblines);
	free(nblines);
	if (nblinesint == row - 1)
		return (1);
	return (0);
}

int		ft_check_line_format(char **map)
{
	int ref_len;
	int i;

	ref_len = ft_strlen(map[1]);
	i = 2;
	while (map[i])
	{
		if (ft_strlen(map[i++]) != ref_len)
			return (0);
	}
	if (map[i - 1][ref_len] != 0)
		return (0);
	return (1);
}

int		ft_check_if_valid(char **map)
{
	char	*buf;
	int		j;
	int		i;
	char	empty;
	char	obs;

	buf = map[0];
	while (*buf != 0)
		buf++;
	empty = *(buf - 3);
	obs = *(buf - 2);
	i = 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != 0)
		{
			if (map[i][j] != empty && map[i][j] != obs)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_check_map(char **map, int row)
{
	if (!(ft_check_first_2_lines(map)))
		return (NULL);
	if (!(ft_check_nb_lines(map, row)))
		return (NULL);
	if (!(ft_check_line_format(map)))
		return (NULL);
	if (!(ft_check_if_valid(map)))
		return (NULL);
	return (map);
}
