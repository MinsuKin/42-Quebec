/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:25:09 by minkim            #+#    #+#             */
/*   Updated: 2022/05/07 14:04:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"

void			param_init(t_param *param)
{
	param->x = 3;
	param->y = 4;
}

int				key_press(int keycode, t_param *param)
{
	// static int a = 0;

	if (keycode == KEY_W)
		param->y++;
	else if (keycode == KEY_S)
		param->y--;
	else if (keycode == KEY_A)
		param->x--;
	else if (keycode == KEY_D)
		param->x++;
	else if (keycode == KEY_ESC)
		exit(0);
	printf("x: %d, y: %d\n", param->x, param->y);
	return (0);
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

int ft_str_free(char *line, t_check *check, char *map)
{
	free(line);
	free(check);
	free(map);
	return (0);
}

int			main(void)
{
	void *mlx;
	void *win;
	void *img;
	void *img2;
	void *img3;
	void *img4;
	void *img5;
	void *img6;
	void *img7;
	int img_width;
	int img_height;
	t_param		param;
	// t_args		args;

	char *map;
	char *lastline;

	int fd;
	char *line;
	t_check *check;
	size_t len;


	fd = open("./map.ber", O_RDONLY);
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
		return (0);
	}

	param_init(&param);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1000, 500, "my_mlx");
	img = mlx_xpm_file_to_image(mlx, "./images/snow-tilemap.xpm", &img_width, &img_height);
	img2 = mlx_xpm_file_to_image(mlx, "./images/icecrystal.xpm", &img_width, &img_height);
	img3 = mlx_xpm_file_to_image(mlx, "./images/character.xpm", &img_width, &img_height);
	img4 = mlx_xpm_file_to_image(mlx, "./images/icecrystal.xpm", &img_width, &img_height);
	img5 = mlx_xpm_file_to_image(mlx, "./images/ice-sword.xpm", &img_width, &img_height);
	img6 = mlx_xpm_file_to_image(mlx, "./images/star-sword.xpm", &img_width, &img_height);
	img7 = mlx_xpm_file_to_image(mlx, "./images/fire-sword.xpm", &img_width, &img_height);
	

	char **two_d_map;

	two_d_map = ft_split(map ,'\n');

	// int j = -1;
	// while(two_d_map[++j])
	// 	printf("%s\n", two_d_map[j]);

	size_t col = ft_strlen(map) / len;

	size_t y = 0;
	while (y < col)
	{
		size_t x = 0;
		while (x < len - 1)
		{
			mlx_put_image_to_window(mlx, win, img, x * 64, y * 64);
			if (two_d_map[y][x] == '1')
				mlx_put_image_to_window(mlx, win, img2, x * 64, y * 64);
			x++;
		}
		y++;
	}


	// mlx_put_image_to_window(mlx, win, img2, 64, 0);
	// mlx_put_image_to_window(mlx, win, img3, 128, 0);
	// mlx_put_image_to_window(mlx, win, img4, 192, 64);
	// mlx_put_image_to_window(mlx, win, img5, 0, 64);
	// mlx_put_image_to_window(mlx, win, img6, 64, 64);
	// mlx_put_image_to_window(mlx, win, img7, 128, 64);
	mlx_hook(win, X_EVENT_KEY_RELEASE, 0, &key_press, &param);
	mlx_loop(mlx);
	return (0);
}