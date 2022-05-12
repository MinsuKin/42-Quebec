/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:25:09 by minkim            #+#    #+#             */
/*   Updated: 2022/05/11 21:32:14 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void	param_init(t_param *param, char *map)
{
	int img_width;
	int img_height;

	param->x = 1;
	param->y = 1;
	param->collected = 0;
	param->mlx = mlx_init();
	param->win = mlx_new_window(param->mlx, 1000, 500, "my_mlx");
	param->tile = mlx_xpm_file_to_image(param->mlx, "./images/snow-tilemap.xpm", &img_width, &img_height);
	param->wall = mlx_xpm_file_to_image(param->mlx, "./images/icecrystal.xpm", &img_width, &img_height);
	param->collect = mlx_xpm_file_to_image(param->mlx, "./images/ice-sword.xpm", &img_width, &img_height);
	param->exit = mlx_xpm_file_to_image(param->mlx, "./images/icebox.xpm", &img_width, &img_height);
	param->player = mlx_xpm_file_to_image(param->mlx, "./images/character.xpm", &img_width, &img_height);
	param->two_d_map = ft_split(map ,'\n');
}

int	move_check(t_param *param, int y, int x)
{
	if (param->two_d_map[y][x] == '0')
		return (1);
	if (param->two_d_map[y][x] == 'P')
		return (1);
	if (param->two_d_map[y][x] == 'C')
	{
		param->collected = 1;
		mlx_put_image_to_window(param->mlx, param->win, param->tile, x * 64, y * 64);
		return (1);
	}
	if (param->two_d_map[y][x] == 'E' && param->collected == 1)
		exit(0);
	return (0);
}

void	move_w(t_param *param)
{
	if (move_check(param, param->y - 1, param->x))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, param->x * 64, (param->y - 1) * 64);
		param->y--;
	}
}

void	move_s(t_param *param)
{
	if (move_check(param, param->y + 1, param->x))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, param->x * 64, (param->y + 1) * 64);
		param->y++;
	}
}

void	move_a(t_param *param)
{
	if (move_check(param, param->y, param->x - 1))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, (param->x - 1) * 64, param->y * 64);
		param->x--;
	}
}

void	move_d(t_param *param)
{
	if (move_check(param, param->y, param->x + 1))
	{
		mlx_put_image_to_window(param->mlx, param->win, param->tile, param->x * 64, param->y * 64);
		mlx_put_image_to_window(param->mlx, param->win, param->player, (param->x + 1) * 64, param->y * 64);
		param->x++;
	}
}

int				key_press(int keycode, t_param *param)
{
	if (keycode == KEY_W)
		move_w(param);
	else if (keycode == KEY_S)
		move_s(param);
	else if (keycode == KEY_A)
		move_a(param);
	else if (keycode == KEY_D)
		move_d(param);
	else if (keycode == KEY_ESC)
		exit(0);
	printf("x: %d, y: %d\n", param->x, param->y);
	return (0);
}

void	ft_error(int exit_code)
{
	perror("Error");
	exit(exit_code);
}

void check_init(t_check *check)
{
	check->collect = 0;
	check->exit = 0;
	check->player = 0;
}

int check_char(char c, t_check *check)
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
	int i;

	i = 0;
	while (line[i])
	{
		if (check_char(line[i], check))
		{
			write(1, "Error\n", 7);
			return (1);
		}
		i++;
	}
	return (0);
}


int check_close(char *line, size_t len)
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
		write(1, "Error\n", 7);
		return (1);
	}
	return (0);
}

int	check_cep(t_check *check)
{
	if (check->collect == 0 || check->exit == 0 || check->player == 0)
	{
		write(1, "Error\n", 7);
		free(check);
		return (1);
	}
	free(check);
	return (0);
}

int	check_line_closed(char *line, size_t len)
{
	size_t i;

	i = 0;
	while (i < len - 1)
	{
		if (line[i] != '1')
		{
			write(1, "Error\n", 7);
			return (1);
		}
		i++;
	}
	return (0);
}

char *ft_str_free(char *line, t_check *check, char *map)
{
	free(line);
	free(check);
	free(map);
	return (NULL);
}

char *check_map(char *file)
{
	int fd;
	char *map;
	char *line;
	char *lastline;
	t_check *check;
	size_t len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error(1);
	line = get_next_line(fd);
	check = (t_check *)malloc(sizeof(t_check));
	check_init(check);
	len = ft_strlen(line);
	map = ft_strndup(line, len);
	if (check_line_closed(line, len))
		return (ft_str_free(line, check, map));
	while (line)
	{
		if (check_rec(line, len))
			return (ft_str_free(line, check, map));
		if (check_line(line, check))
			return (ft_str_free(line, check, map));
		lastline = ft_strndup(line, len);
		free(line);
		line = get_next_line(fd);
		if (line)
			map = ft_strjoin(map, line);
		else if (check_line_closed(lastline, len))
		{
			free(lastline);
			return (ft_str_free(line, check, map));
		}
		free(lastline);
	}
	if (check_cep(check))
	{
		free(map);
		return (NULL);
	}
	return (map);
}

size_t	ft_strlen_n(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count] != '\n')
		count++;
	return (count);
}

void	ft_render(t_param *param, char *map)
{
	int row;
	int col;
	int y;
	int x;

	row = ft_strlen_n(map);
	col = ft_strlen(map) / row;
	y = 0;
	while (y < col)
	{
		x = 0;
		while (x < row - 1)
		{
			mlx_put_image_to_window(param->mlx, param->win, param->tile, x * 64, y * 64);
			if (param->two_d_map[y][x] == '1')
				mlx_put_image_to_window(param->mlx, param->win, param->wall, x * 64, y * 64);
			else if (param->two_d_map[y][x] == 'C')
				mlx_put_image_to_window(param->mlx, param->win, param->collect, x * 64, y * 64);
			else if (param->two_d_map[y][x] == 'E')
				mlx_put_image_to_window(param->mlx, param->win, param->exit, x * 64, y * 64);
			else if (param->two_d_map[y][x] == 'P')
			{
				mlx_put_image_to_window(param->mlx, param->win, param->player, x * 64, y * 64);
				param->x = x;
				param->y = y;
			}
			x++;
		}
		y++;
	}
}

int			main(int argc, char **argv)
{
	t_param	param;
	char *map;

	if (argc != 2)
		ft_error(1);
	map = check_map(argv[1]);
	if (map == NULL)
		return (0);
	param_init(&param, map);
	ft_render(&param, map);
	free(map);
	mlx_hook(param.win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
	mlx_loop(param.mlx);
	return (0);
}
