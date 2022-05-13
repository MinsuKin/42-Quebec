/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 14:02:10 by minkim            #+#    #+#             */
/*   Updated: 2022/05/13 15:48:15 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

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
char	*ft_strchr(char *str, char c);

int		ft_put_conv(t_args *args, va_list ap);
int		ft_strlen(char *s);
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
