/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:54 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 16:18:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(t_node *ahead)
{
	insert(ahead->prev, ahead->next->data);
	delete(ahead, ahead->next);
	print_cmd(ahead, 3);
}

void	rotate_b(t_node *ahead, t_node *bhead)
{
	insert(bhead->prev, bhead->next->data);
	delete(bhead, bhead->next);
	print_cmd(ahead, 4);
}

void	rotate_ab(t_node *ahead, t_node *bhead)
{
	insert(ahead->prev, ahead->next->data);
	delete(ahead, ahead->next);
	insert(bhead->prev, bhead->next->data);
	delete(bhead, bhead->next);
	write(1, "rr\n", 3);
}
