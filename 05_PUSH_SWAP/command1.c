/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:54 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 16:18:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_node *ahead)
{
	int	tmp;

	tmp = ahead->next->data;
	ahead->next->data = ahead->next->next->data;
	ahead->next->next->data = tmp;
	print_cmd(ahead, 1);
}

void	swap_b(t_node *ahead, t_node *bhead)
{
	int	tmp;

	tmp = bhead->next->data;
	bhead->next->data = bhead->next->next->data;
	bhead->next->next->data = tmp;
	print_cmd(ahead, 2);
}

void	swap_ab(t_node *ahead, t_node *bhead)
{
	int	atmp;
	int	btmp;

	atmp = ahead->next->data;
	ahead->next->data = ahead->next->next->data;
	ahead->next->next->data = atmp;
	btmp = bhead->next->data;
	bhead->next->data = bhead->next->next->data;
	bhead->next->next->data = btmp;
	write(1, "ss\n", 3);
}

void	push_a(t_node *ahead, t_node *bhead)
{
	if (bhead == bhead->next)
		return ;
	insert(ahead, bhead->next->data);
	delete(bhead, bhead->next);
	print_cmd(ahead, 5);
}

void	push_b(t_node *ahead, t_node *bhead)
{
	if (ahead == ahead->next)
		return ;
	insert(bhead, ahead->next->data);
	delete(ahead, ahead->next);
	print_cmd(ahead, 6);
}
