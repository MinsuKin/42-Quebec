/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 18:08:23 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	atob_exit(t_node *ahead, t_node *bhead, int size)
{
	if (size == 4)
		ft_four_a(ahead, bhead);
	else if (size == 3)
		ft_three_a(ahead, bhead);
	else if (size == 2)
		ft_two(ahead);
}

void	btoa_exit(t_node *ahead, t_node *bhead, int size)
{
	if (size == 4)
		ft_four_b(ahead, bhead);
	else if (size == 3)
		ft_three_b(ahead, bhead);
	else if (size == 2)
	{
		ft_two_b(ahead, bhead);
		swap_b(ahead, bhead);
		push_a(ahead, bhead);
		push_a(ahead, bhead);
	}
	else if (size == 1)
		push_a(ahead, bhead);
}

int	rra_util(t_node *ahead, int cnt)
{
	reverse_rotate_a(ahead);
	cnt++;
	return (cnt);
}

int	rrb_util(t_node *ahead, t_node *bhead, int cnt)
{
	reverse_rotate_b(ahead, bhead);
	cnt++;
	return (cnt);
}

int	rrr_util(t_node *ahead, t_node *bhead, int cnt)
{
	reverse_rotate_ab(ahead, bhead);
	cnt++;
	return (cnt);
}
