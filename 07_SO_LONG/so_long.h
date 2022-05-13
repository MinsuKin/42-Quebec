/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:10:47 by minkim            #+#    #+#             */
/*   Updated: 2022/05/13 19:16:48 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_KEY_EXIT			17 //exit key code

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

// typedef struct s_img
// {
// 	void	*tile;
// 	void	*wall;
// 	void	*collect;
// 	void	*exit;
// 	void	*player;
// }				t_img;

typedef struct s_param
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		collected;
	int		cnt;
	int		collect_cnt;
	char	**two_d_map;
	void	*tile;
	void	*wall;
	void	*collect;
	void	*exit;
	void	*player;
}				t_param;

typedef struct s_check
{
	int		collect;
	int		exit;
	int		player;
}				t_check;

// typedef struct s_check
// {
// 	int		collect;
// 	int		exit;
// 	int		player;
// 	char	*line;
// 	char	*lastline;
// 	char	*map;
// }				t_check;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	**ft_split(char const *s, char c);

char	*get_next_line(int fd);

char	*ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

typedef struct s_args
{
	int	c;
	int	width;
	int	has_width;
	int	precision;
	int	has_precision;
}				t_args;

int		ft_printf(const char *format, ...);

void	initialize_args(t_args *args);
char	*read_args(t_args *args, char *itr);
char	*ft_strchrr(char *str, char c);
int		ft_put_conv(t_args *args, va_list ap);
int		ft_strlenn(char *s);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_put_s(va_list ap);
int		ft_put_c(va_list ap);
int		ft_put_d(va_list ap);
int		ft_puti(int d);
int		ft_put_x(t_args *args, va_list ap);
int		ft_putx(unsigned int ud);
int		ft_putxx(unsigned int ud);
int		ft_put_u(va_list ap);
int		ft_putu(unsigned int u);
int		ft_put_p(va_list ap);
int		ft_putp(unsigned long ul);

#endif
