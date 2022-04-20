/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:58 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 17:08:48 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_two(t_node *ahead)
{
	if (ahead->next->data > ahead->next->next->data)
		swap_a(ahead);
}

void	ft_three(t_node *ahead)
{
	if (ahead->next->data > ahead->next->next->data)
	{
		if (ahead->next->data > ahead->next->next->next->data)
			rotate_a(ahead);
		if (ahead->next->data > ahead->next->next->data)
			swap_a(ahead);
	}
	else
	{
		if (ahead->next->data > ahead->next->next->next->data)
			reverse_rotate_a(ahead);
		else
		{
			if (ahead->next->next->data > ahead->next->next->next->data)
			{
				swap_a(ahead);
				rotate_a(ahead);
			}
		}
	}
}

void	ft_four(t_node *ahead, t_node *bhead)
{
	int	sml;

	sml = find_sml(ahead, 4);
	while (1)
	{
		if (ahead->next->data == sml)
		{
			push_b(ahead, bhead);
			break ;
		}
		rotate_a(ahead);
	}
	ft_three(ahead);
	push_a(ahead, bhead);
}

void	ft_five_util(t_node *ahead, t_node *bhead, int big)
{
	ft_three(ahead);
	push_a(ahead, bhead);
	if (bhead->next->data == big)
	{
		push_a(ahead, bhead);
		rotate_a(ahead);
	}
	else
	{
		rotate_a(ahead);
		push_a(ahead, bhead);
	}
}

void	ft_five(t_node *ahead, t_node *bhead)
{
	int	cnt;
	int	sml;
	int	big;

	sml = find_sml(ahead, 5);
	big = find_big(ahead, 5);
	cnt = 0;
	while (cnt != 2)
	{
		if (ahead->next->data == sml || ahead->next->data == big)
		{
			push_b(ahead, bhead);
			cnt++;
		}
		if (ahead->next->data == sml || ahead->next->data == big)
		{
			push_b(ahead, bhead);
			cnt++;
		}
		if (cnt == 2)
			break ;
		rotate_a(ahead);
	}
	ft_five_util(ahead, bhead, big);
}
