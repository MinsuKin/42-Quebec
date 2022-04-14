/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:43 by minkim            #+#    #+#             */
/*   Updated: 2022/04/13 17:56:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void init(Node *phead) {
	phead->prev = phead;
	phead->next = phead;
}

void insert(Node *before, int data) {
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->prev = before;
	newnode->next = before->next;
	before->next->prev = newnode;
	before->next = newnode;
}
// pop_left
void delete(Node *head, Node *removed) {
	if (removed == head) return;
	head->next = removed->next;
	removed->next->prev = removed->prev;
	free(removed);
}
// pop
void delete_tail(Node *tail, Node *removed) {
	if (removed == tail) return;
	tail->prev = removed->prev;
	removed->prev->next = removed->next;
	free(removed);
}

void ft_free(Node *phead)
{
	Node *p;
	p = phead->next;
	while (p != phead) 
	{
		p = p->next;
		free(p->prev);
	}
}
