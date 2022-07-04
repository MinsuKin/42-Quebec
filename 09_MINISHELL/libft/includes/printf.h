/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:01:53 by tgarriss          #+#    #+#             */
/*   Updated: 2022/04/05 14:16:16 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

// ft_printf.c
int		ft_printf(int fd, const char *string, ...);
void	dispatch(va_list *ap, char type, int *bytes, int fd);

// ft_printf_utils.c
void	putaddr_fd(long n, int prefix, int fd, int *bytes);
void	putchar_fd(char c, int fd, int *bytes);
void	puthexa_fd(long n, char flag, int fd, int *bytes);
void	putstr_fd(char *s, int fd, int *bytes);
void	putnbr_fd(int n, int fd, int *bytes);
// ft_printf_utils2.c
void	putunbr_fd(int n, int fd, int *bytes);

#endif
