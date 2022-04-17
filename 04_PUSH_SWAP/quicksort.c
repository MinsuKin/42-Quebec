/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/16 17:51:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void atob(Node *ahead, Node *bhead, int size)
{
	
	int cnt;
	int ra;
	int rb;
	int pb;
	
	if (size <= 4)
	{
		if (size == 4)
			ft_four_a(ahead, bhead);
		else if (size == 3)
			ft_three_a(ahead, bhead);
		else if (size == 2)
			ft_two(ahead);
		return;
	}
	ra = 0;
	rb = 0;
	pb = 0;
	cnt = 0;
    int one_third = find_one_third(ahead, size);
    int two_third = find_two_third(ahead, size);
	while (cnt < size)
	{
		if (ahead->next->data >= two_third)
		{
			rotate_a(ahead);
			ra++;
		}
		else
		{
			push_b(ahead, bhead);
			pb++;
			if (bhead->next->data >= one_third)
			{
				rotate_b(ahead, bhead);
				rb++;
			}
		}
		cnt++;
	}
	cnt = 0;
	while (cnt < ra && cnt < rb)
	{
		reverse_rotate_ab(ahead, bhead);
		cnt++;
	}
	while (cnt < ra)
	{
		reverse_rotate_a(ahead);
		cnt++;
	}
	while (cnt < rb)
	{
		reverse_rotate_b(ahead, bhead);
		cnt++;
	}
	atob(ahead, bhead, ra);
	btoa(ahead, bhead, rb);
	btoa(ahead, bhead, pb - rb);
}

void btoa(Node *ahead, Node *bhead, int size)
{
	int rb;
	int ra;
	int pa;
	int cnt;

	if (size <= 4)
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
		return;
	}
	rb = 0;
	ra = 0;
	pa = 0;
	cnt = 0;
    int one_third = find_one_third(bhead, size);
    int two_third = find_two_third(bhead, size);
	while (cnt < size)
	{
		if (bhead->next->data < one_third)
		{
			rotate_b(ahead, bhead);
			rb++;
		}
		else
		{
			push_a(ahead, bhead);
			pa++;
			if (ahead->next->data < two_third)
			{
				rotate_a(ahead);
				ra++;
			}
		}
		cnt++;
	}
	atob(ahead, bhead, pa - ra);
	cnt = 0;
	while (cnt < ra && cnt < rb)
	{
		reverse_rotate_ab(ahead, bhead);
		cnt++;
	}
	while (cnt < ra)
	{
		reverse_rotate_a(ahead);
		cnt++;
	}
	while (cnt < rb)
	{
		reverse_rotate_b(ahead, bhead);
		cnt++;
	}
	atob(ahead, bhead, ra);
	btoa(ahead, bhead, rb);
}
