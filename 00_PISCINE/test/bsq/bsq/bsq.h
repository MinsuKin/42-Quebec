/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 07:59:12 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/01 10:33:16 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdio.h> // REMOVE BEFORE FINAL PUSH // REMOVE BEFORE FINAL PUSH //

# include <fcntl.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# define BUF_SIZE 4096

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
void	ft_input_to_tab(char *str);
int		size;
int		char_empty;
int		char_obs;
int		char_fill;

#endif
