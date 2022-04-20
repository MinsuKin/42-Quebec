/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:58 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 17:38:38 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_three_a_util(t_node *ahead, t_node *bhead)
{
	if (ahead->next->next->data < ahead->next->next->next->data)
	{
		if (ahead->next->data > ahead->next->next->next->data)
		{
			swap_a(ahead);
			push_b(ahead, bhead);
			swap_a(ahead);
			push_a(ahead, bhead);
		}
		else
			swap_a(ahead);
	}
	else
	{
		if (ahead->next->data > ahead->next->next->next->data)
		{
			swap_a(ahead);
			push_b(ahead, bhead);
			swap_a(ahead);
			push_a(ahead, bhead);
			swap_a(ahead);
		}
	}
}

void	ft_three_b_util(t_node *ahead, t_node *bhead)
{
	if (bhead->next->data > bhead->next->next->next->data)
	{
		push_a(ahead, bhead);
		swap_b(ahead, bhead);
		push_a(ahead, bhead);
		push_a(ahead, bhead);
	}
	else
	{
		push_a(ahead, bhead);
		swap_b(ahead, bhead);
		push_a(ahead, bhead);
		swap_a(ahead);
		push_a(ahead, bhead);
	}
}

void	ft_three_b_util2(t_node *ahead, t_node *bhead)
{
	if (bhead->next->data < bhead->next->next->next->data)
	{
		swap_b(ahead, bhead);
		push_a(ahead, bhead);
		swap_b(ahead, bhead);
		push_a(ahead, bhead);
		push_a(ahead, bhead);
	}
	else
	{
		swap_b(ahead, bhead);
		push_a(ahead, bhead);
		push_a(ahead, bhead);
		push_a(ahead, bhead);
	}
}

void	ft_three_b_util3(t_node *ahead, t_node *bhead)
{
	swap_b(ahead, bhead);
	push_a(ahead, bhead);
	swap_b(ahead, bhead);
	push_a(ahead, bhead);
	swap_a(ahead);
	push_a(ahead, bhead);
}
