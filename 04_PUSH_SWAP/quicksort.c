/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/13 19:48:11 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// void atob1(Node *ahead, Node *bhead, int size)
// {
	
// 	int cnt;
// 	int ra;
// 	int pb;
// 	int mid;
	
// 	if (size <= 2)
// 	{
// 		if (size == 2)
// 			ft_two(ahead);
// 		return;
// 	}
// 	ra = 0;
// 	pb = 0;
// 	cnt = 0;
// 	mid = find_mid(ahead, size);
// 	while (cnt < size)
// 	{
// 		if (ahead->next->data > mid)
// 		{
// 			rotate_a(ahead);
// 			ra++;
// 		}
// 		else
// 		{
// 			push_b(ahead, bhead);
// 			pb++;
// 		}
// 		cnt++;
// 	}
// 	cnt = 0;
// 	while (cnt < ra)
// 	{
// 		reverse_rotate_a(ahead);
// 		cnt++;
// 	}
// 	atob1(ahead, bhead, ra);
// 	btoa1(ahead, bhead, pb);
// }

// void btoa1(Node *ahead, Node *bhead, int size)
// {
// 	int rb;
// 	int pa;
// 	int cnt;
// 	int mid;

// 	if (size <= 2)
// 	{
// 		if (size == 2)
// 		{
// 			ft_two_b(bhead);
// 			swap_b(bhead);
// 			push_a(ahead, bhead);
// 			push_a(ahead, bhead);
// 		}
// 		else if (size == 1)
// 			push_a(ahead, bhead);
// 		return;
// 	}
// 	rb = 0;
// 	pa = 0;
// 	cnt = 0;
// 	mid = find_mid(bhead, size);
// 	while (cnt < size)
// 	{
// 		if (bhead->next->data < mid)
// 		{
// 			rotate_b(bhead);
// 			rb++;
// 		}
// 		else
// 		{
// 			push_a(ahead, bhead);
// 			pa++;
// 		}
// 		cnt++;
// 	}
// 	cnt = 0;
// 	while (cnt < rb)
// 	{
// 		reverse_rotate_b(bhead);
// 		cnt++;
// 	}
// 	atob1(ahead, bhead, pa);
// 	btoa1(ahead, bhead, rb);
// }
