/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 18:31:05 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	atob(t_node *ahead, t_node *bhead, int size, int cnt)
{
	int	ra;
	int	rb;
	int	pb;
	int	one_third;
	int	two_third;

	if (size <= 4)
	{
		atob_exit(ahead, bhead, size);
		return ;
	}
	ra = 0;
	rb = 0;
	pb = 0;
	one_third = find_one_third(ahead, size);
	two_third = find_two_third(ahead, size);
	while (size--)
	{
		if (ahead->next->data >= two_third)
			ra = ra_util(ahead, ra);
		else
		{
			pb = pb_util(ahead, bhead, pb);
			if (bhead->next->data >= one_third)
				rb = rb_util(ahead, bhead, rb);
		}
	}
	while (cnt < ra && cnt < rb)
		cnt = rrr_util(ahead, bhead, cnt);
	while (cnt < ra)
		cnt = rra_util(ahead, cnt);
	while (cnt < rb)
		cnt = rrb_util(ahead, bhead, cnt);
	atob(ahead, bhead, ra, 0);
	btoa(ahead, bhead, rb, 0);
	btoa(ahead, bhead, pb - rb, 0);
}

void	btoa(t_node *ahead, t_node *bhead, int size, int cnt)
{
	int	rb;
	int	ra;
	int	pa;
	int	one_third;
	int	two_third;

	if (size <= 4)
	{
		btoa_exit(ahead, bhead, size);
		return ;
	}
	rb = 0;
	ra = 0;
	pa = 0;
	one_third = find_one_third(bhead, size);
	two_third = find_two_third(bhead, size);
	while (size--)
	{
		if (bhead->next->data < one_third)
			rb = rb_util(ahead, bhead, rb);
		else
		{
			pa = pa_util(ahead, bhead, pa);
			if (ahead->next->data < two_third)
				ra = ra_util(ahead, ra);
		}
	}
	atob(ahead, bhead, pa - ra, 0);
	while (cnt < ra && cnt < rb)
		cnt = rrr_util(ahead, bhead, cnt);
	while (cnt < ra)
		cnt = rra_util(ahead, cnt);
	while (cnt < rb)
		cnt = rrb_util(ahead, bhead, cnt);
	atob(ahead, bhead, ra, 0);
	btoa(ahead, bhead, rb, 0);
}
