/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:25:09 by minkim            #+#    #+#             */
/*   Updated: 2022/05/14 18:02:09 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_param	param;
	char	*map;
	int		fd;

	if (argc != 2)
		ft_error(1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error(0);
	map = check_map(fd);
	if (map == NULL)
		return (0);
	param_init(&param, map);
	ft_render(&param, map);
	free(map);
	mlx_hook(param.win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
	mlx_hook(param.win, X_EVENT_KEY_EXIT, 0, &exit_game, &param);
	mlx_loop(param.mlx);
	return (0);
}
