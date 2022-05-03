/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 07:01:25 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/04 08:14:19 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char			**ft_get_lines_from_grid(char *path);
char			**ft_check_map(char **map, int row);
char			*ft_file_missing(void);
char			**ft_split(char *str, char *charset);

int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				ft_row_len(char **lines);

void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_error(char *str);

typedef struct	s_map {
	int		row;
	int		col;
	char	empty;
	char	obs;
	char	fill;
	char	**map;
	int		x_bsq;
	int		y_bsq;
}				t_map;

void			ft_do_square(t_map map);

#endif
