/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:25:09 by minkim            #+#    #+#             */
/*   Updated: 2022/05/14 18:14:18 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_char(char c, t_check *check)
{
	if (c == '\n')
		return (0);
	else if (c == '1')
		return (0);
	else if (c == '0')
		return (0);
	else if (c == 'C')
	{	
		check->collect++;
		return (0);
	}
	else if (c == 'E')
	{	
		check->exit++;
		return (0);
	}
	else if (c == 'P')
	{	
		check->player++;
		return (0);
	}
	else
		return (1);
}

int	check_line(char *line, t_check *check)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (check_char(line[i], check))
		{
			write(1, "Error : this map is not valid.\n", 32);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_close(char *line, size_t len)
{
	if (line[0] == '1' && line[len - 2] == '1')
		return (0);
	else
		return (1);
}

int	check_rec(char *line, size_t len)
{
	if (len != ft_strlen(line) || check_close(line, len))
	{
		write(1, "Error : map must be rectangular.\n", 34);
		return (1);
	}
	return (0);
}

char	*check_cep(t_check *check, char *map)
{
	if (check->collect == 0 || check->exit == 0 || check->player == 0)
	{
		write(1, "Error : map must have at least one C/E/P each.\n", 48);
		free(map);
		return (NULL);
	}
	return (map);
}
