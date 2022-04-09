/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsu <minsu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:21 by minkim            #+#    #+#             */
/*   Updated: 2022/04/01 19:51:56 by minsu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>

typedef struct	s_dllst
{
	int			    data;
	struct s_dllst	*prev;
	struct s_dllst	*next;
}					t_stack;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);

#endif