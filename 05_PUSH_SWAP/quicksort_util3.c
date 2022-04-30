/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_util3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 19:27:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	atob_exit_util(t_node *ahead, t_node *bhead, int size, t_args *args)
{
	if (size <= 4)
	{
		atob_exit(ahead, bhead, size);
		free(args);
		return (1);
	}
	return (0);
}

int	btoa_exit_util(t_node *ahead, t_node *bhead, int size, t_brgs *brgs)
{
	if (size <= 4)
	{
		btoa_exit(ahead, bhead, size);
		free(brgs);
		return (1);
	}
	return (0);
}

void	init_args(t_args *args, t_node *ahead, int size)
{
	args->rb = 0;
	args->ra = 0;
	args->pb = 0;
	args->one_third = find_one_third(ahead, size);
	args->two_third = find_two_third(ahead, size);
}

void	init_brgs(t_brgs *brgs, t_node *bhead, int size)
{
	brgs->rb = 0;
	brgs->ra = 0;
	brgs->pa = 0;
	brgs->one_third = find_one_third(bhead, size);
	brgs->two_third = find_two_third(bhead, size);
}
