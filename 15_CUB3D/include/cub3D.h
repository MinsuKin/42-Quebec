/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:32:36 by chughes           #+#    #+#             */
/*   Updated: 2023/02/02 15:44:54 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>

# include <stdlib.h>	// malloc, free, exit
# include <fcntl.h>		// open
# include <unistd.h>	// close, read
# include <stdio.h>		// printf, perror
# include <stdbool.h>	// bool

# include "cub3D_defines.h"

// Data struct with window data
typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*addr;
	int		endian;
	void	*img;
	int		bpp;
	int		line_size;

	char	**map_file;
	char	*tex_path[4];
	char	*floor_name;
	char	*ceiling_name;

	int		**tex;
	int		floor;
	int		ceiling;
	int		width;
	int		height;
	int		**map;

	double	pos[2];
	double	dir[2];
	double	plane[2];
}			t_data;

// MLX image information
typedef struct s_img {
	void	*img;
	void	*addr;
	int		l_size;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}			t_img;

// Frame information
typedef struct s_frame {
	int		x;
	double	camera_x;
	double	ray_dir[2];
	int		map[2];
	double	side_dst[2];
	double	delta_dst[2];
	double	perp_dst;
	int		step[2];
	int		side;
	bool	hit;
	int		line_height;
	double	wall_x;
	double	draw_start;
	double	draw_end;
	int		tex[2];
}			t_frame;

// Libft functions
void	*xalloc(size_t nitems, size_t size);
void	*xfree(void *ptr);
char	*gnl(int fd);
int		ft_atoi(const char *str);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
int		ft_linelen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*str_append(char *s1, char *s2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		arraylen(char **array);
char	**arraydup(char **array);
char	**array_realloc(char **ptr, int size);
char	**array_del_one(char **array, int position);
char	**free_array(char **array);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*strpop(char *str, int position);

// Data setup and teardown functions
t_data	*get_data(void);
void	init_data(int argc, char *argv[]);
void	del_data(void);

// Map parsing checks
void	check_input(int argc, char *path);
void	read_map(char *map_name);
void	parse_map(void);
void	grab_textures(void);
void	set_texture(int *i, int side);
void	grab_colors(void);
void	grab_map(void);
void	copy_map(void);
void	init_player(char direction, int x, int y);
void	get_size(void);
void	set_colors(void);
void	exit_error(char *message);
void	check_map(void);
int		check_last_row(void);
int		check_closed_first_zero(void);
int		flood_fill_first_zero(int x, int y);
int		check_closed_player(void);
int		check_space(void);
int		check_player(void);
void	check_numbers(char **floor, char **ceiling);
int		check_division(int i, int j);
int		check_division_space(int i, int j);
int		check_right_upndown(int i, int j);
int		check_left_upndown(int i, int j);

// MLX interop functions
void	close_window(t_data **data);
int		render_frame(void);
int		exit_window(int keycode, t_data **data);
void	close_window(t_data **data);
int		keydown(int keycode, t_data **data);
void	mlx_pixel_img(int x, int y, int color);
void	load_textures(t_data *data);

// Movement functions
void	move_north(t_data **data);
void	move_west(t_data **data);
void	move_south(t_data **data);
void	move_east(t_data **data);
void	look_left(t_data **data);
void	look_right(t_data **data);

// Render utils
void	ray_direction(t_data *data, t_frame *frame);
void	ray_length(t_frame *frame);
void	side_distance(t_data *d, t_frame *f);
void	check_hit(t_data *data, t_frame *frame);

#endif // CUB3D_H
