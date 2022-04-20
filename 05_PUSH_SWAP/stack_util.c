/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:43 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 16:18:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init(t_node *phead)
{
	phead->prev = phead;
	phead->next = phead;
}

void	insert(t_node *before, int data)
{
	t_node	*newt_node;

	newt_node = (t_node *)malloc(sizeof(t_node));
	newt_node->data = data;
	newt_node->prev = before;
	newt_node->next = before->next;
	before->next->prev = newt_node;
	before->next = newt_node;
}

void	delete(t_node *head, t_node *removed)
{
	if (removed == head)
		return ;
	head->next = removed->next;
	removed->next->prev = removed->prev;
	free(removed);
}

void	delete_tail(t_node *tail, t_node *removed)
{
	if (removed == tail)
		return ;
	tail->prev = removed->prev;
	removed->prev->next = removed->next;
	free(removed);
}

void	ft_free(t_node *phead)
{
	t_node	*p;

	p = phead->next;
	while (p != phead)
	{
		p = p->next;
		free(p->prev);
	}
}
