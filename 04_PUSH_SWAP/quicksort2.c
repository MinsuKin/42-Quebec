/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/14 16:07:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void atob(Node *ahead, Node *bhead, int size)
{
	
	int cnt;
	int ra;
	int rb;
	int pb;
	
	if (size <= 3)
	{
		if (size == 3)
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
				rotate_b(bhead);
				rb++;
			}
		}
		cnt++;
	}
    // printf("A_ra = %d\n", ra);
    // printf("A_rb = %d\n", rb);
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
		reverse_rotate_b(bhead);
		cnt++;
	}
    // printf("a1/3 = %d\n", one_third);
    // printf("a2/3 = %d\n", two_third);
	// print_list(ahead);
	// print_list(bhead);
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

	if (size <= 3)
	{
		if (size == 3)
			ft_three_b(ahead, bhead);
		else if (size == 2)
		// if (size == 2)
		{
			ft_two_b(bhead);
			swap_b(bhead);
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
			rotate_b(bhead);
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
    // printf("b1/3 = %d\n", one_third);
    // printf("b2/3 = %d\n", two_third);
    // printf("B_ra = %d\n", ra);
    // printf("B_rb = %d\n", rb);
	// print_list(ahead);
	// print_list(bhead);
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
		reverse_rotate_b(bhead);
		cnt++;
	}
	atob(ahead, bhead, ra);
	btoa(ahead, bhead, rb);
}
