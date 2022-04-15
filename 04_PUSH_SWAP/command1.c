/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:54 by minkim            #+#    #+#             */
/*   Updated: 2022/04/14 21:22:15 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// sa : swap a - 스택 a의 가장 위에 있는 두 원소(혹은 첫 번쨰 원소와 두 번째 원소)의 위치를 서로 바꾼다.
void swap_a(Node *ahead)
{
	int tmp;
	tmp = ahead->next->data;
	ahead->next->data = ahead->next->next->data;
	ahead->next->next->data = tmp;
	write(1, "sa\n", 3);
}
// sb : swap b - 스택 b의 가장 위에 있는 두 원소(혹은 첫 번쨰 원소와 두 번째 원소)의 위치를 서로 바꾼다.
void swap_b(Node *bhead)
{
	int tmp;
	tmp = bhead->next->data;
	bhead->next->data = bhead->next->next->data;
	bhead->next->next->data = tmp;
	write(1, "sb\n", 3);
}
// ss : sa와 sb를 동시에 실행한다.
void swap_ab(Node *ahead, Node *bhead)
{
	int atmp;
	int btmp;
	atmp = ahead->next->data;
	ahead->next->data = ahead->next->next->data;
	ahead->next->next->data = atmp;
	btmp = bhead->next->data;
	bhead->next->data = bhead->next->next->data;
	bhead->next->next->data = btmp;
	write(1, "ss\n", 3);
}
// pa : push a - 스택 b에서 가장 위(탑)에 있는 원소를 가져와서, 스택 a의 맨 위(탑)에 넣는다. 스택 b가 비어 있으면 아무 것도 하지 않는다.
void push_a(Node *ahead, Node *bhead)
{
	if (bhead == bhead->next) return;
	insert(ahead, bhead->next->data);
	delete(bhead, bhead->next);
	write(1, "pa\n", 3);
}
// pb : push b - 스택 a에서 가장 위(탑)에 있는 원소를 가져와서, 스택 b의 맨 위(탑)에 넣는다. 스택 a가 비어있으면 아무 것도 하지 않는다.
void push_b(Node *ahead, Node *bhead)
{
	if (ahead == ahead->next) return;
	insert(bhead, ahead->next->data);
	delete(ahead, ahead->next);
	write(1, "pb\n", 3);
}
