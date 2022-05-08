/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:25:09 by minkim            #+#    #+#             */
/*   Updated: 2022/05/08 16:36:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void			param_init(t_param *param)
{
	param->x = 1;
	param->y = 1;
	param->mlx = mlx_init();
	param->win = mlx_new_window(param->mlx, 1000, 500, "my_mlx");
}

int				key_press(int keycode, t_param *param)
{
	// static int a = 0;

	if (keycode == KEY_W)
		param->y++; //move_w(param);
	else if (keycode == KEY_S)
		param->y--; //move_s(param);
	else if (keycode == KEY_A)
		param->x--; //move_a(param);
	else if (keycode == KEY_D)
		param->x++; //move_d(param);
	else if (keycode == KEY_ESC)
		exit(0); //exit_game(param);
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

int			main(int argc, char **argv)
{
	int img_width;
	int img_height;
	char **two_d_map;
	t_param		param;
	size_t col;
	size_t x;
	size_t y;
	t_img img;


	char *map;
	size_t row;

	if (argc != 2)
		ft_error(1);
	
	map = check_map(argv[1]);
	if (map == NULL)
		return (0);

	param_init(&param);
	img.tile = mlx_xpm_file_to_image(param.mlx, "./images/snow-tilemap.xpm", &img_width, &img_height);
	img.wall = mlx_xpm_file_to_image(param.mlx, "./images/icecrystal.xpm", &img_width, &img_height);
	img.collect = mlx_xpm_file_to_image(param.mlx, "./images/ice-sword.xpm", &img_width, &img_height);
	img.exit = mlx_xpm_file_to_image(param.mlx, "./images/icebox.xpm", &img_width, &img_height);
	img.player = mlx_xpm_file_to_image(param.mlx, "./images/character.xpm", &img_width, &img_height);
	
	two_d_map = ft_split(map ,'\n');

	// int j = -1;
	// while(two_d_map[++j])
	// 	printf("%s\n", two_d_map[j]);

	row = ft_strlen_n(map);
	col = ft_strlen(map) / row;

	y = 0;
	while (y < col)
	{
		x = 0;
		while (x < row - 1)
		{
			mlx_put_image_to_window(param.mlx, param.win, img.tile, x * 64, y * 64);
			if (two_d_map[y][x] == '1')
				mlx_put_image_to_window(param.mlx, param.win, img.wall, x * 64, y * 64);
			else if (two_d_map[y][x] == 'C')
				mlx_put_image_to_window(param.mlx, param.win, img.collect, x * 64, y * 64);
			else if (two_d_map[y][x] == 'E')
				mlx_put_image_to_window(param.mlx, param.win, img.exit, x * 64, y * 64);
			else if (two_d_map[y][x] == 'P')
			{
				mlx_put_image_to_window(param.mlx, param.win, img.player, x * 64, y * 64);
				param.x = x;
				param.y = y;
			}
			x++;
		}
		y++;
	}


	mlx_hook(param.win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
	mlx_loop(param.mlx);
	return (0);
}
