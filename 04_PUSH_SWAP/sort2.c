/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:58 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 17:38:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_two_b(t_node *ahead, t_node *bhead)
{
	if (bhead->next->data > bhead->next->next->data)
		swap_b(ahead, bhead);
}

void	ft_three_a(t_node *ahead, t_node *bhead)
{
	if (ahead->next->data > ahead->next->next->data)
		ft_three_a_util(ahead, bhead);
	else
	{
		if (ahead->next->next->data > ahead->next->next->next->data)
		{
			if (ahead->next->data < ahead->next->next->next->data)
			{
				push_b(ahead, bhead);
				swap_a(ahead);
				push_a(ahead, bhead);
			}
			else
			{
				push_b(ahead, bhead);
				swap_a(ahead);
				push_a(ahead, bhead);
				swap_a(ahead);
			}
		}
	}
}

void	ft_three_b(t_node *ahead, t_node *bhead)
{
	if (bhead->next->data > bhead->next->next->data)
	{
		if (bhead->next->next->data < bhead->next->next->next->data)
			ft_three_b_util(ahead, bhead);
		else
		{
			if (bhead->next->data > bhead->next->next->next->data)
			{
				push_a(ahead, bhead);
				push_a(ahead, bhead);
				push_a(ahead, bhead);
			}
		}
	}
	else
	{
		if (bhead->next->next->data > bhead->next->next->next->data)
			ft_three_b_util2(ahead, bhead);
		else
			ft_three_b_util3(ahead, bhead);
	}
}

void	ft_four_a(t_node *ahead, t_node *bhead)
{
	int	sml;
	int	ra;

	ra = 0;
	sml = find_sml(ahead, 4);
	while (1)
	{
		if (ahead->next->data == sml)
		{
			push_b(ahead, bhead);
			break ;
		}
		rotate_a(ahead);
		ra++;
	}
	while (ra--)
		reverse_rotate_a(ahead);
	ft_three_a(ahead, bhead);
	push_a(ahead, bhead);
}

void	ft_four_b(t_node *ahead, t_node *bhead)
{
	int	big;
	int	rb;

	rb = 0;
	big = find_big(bhead, 4);
	while (1)
	{
		if (bhead->next->data == big)
		{
			push_a(ahead, bhead);
			break ;
		}
		rotate_b(ahead, bhead);
		rb++;
	}
	while (rb--)
		reverse_rotate_b(ahead, bhead);
	ft_three_b(ahead, bhead);
}
