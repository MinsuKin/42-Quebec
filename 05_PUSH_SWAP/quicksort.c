/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 15:58:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	atob_util(t_node *ahead, t_node *bhead, t_args *args)
{
	args->pb = pb_util(ahead, bhead, args->pb);
	if (bhead->next->data >= args->one_third)
		args->rb = rb_util(ahead, bhead, args->rb);
}

void	btoa_util(t_node *ahead, t_node *bhead, t_brgs *brgs)
{
	brgs->pa = pa_util(ahead, bhead, brgs->pa);
	if (ahead->next->data < brgs->two_third)
		brgs->ra = ra_util(ahead, brgs->ra);
}

void	atob(t_node *ahead, t_node *bhead, int size, int cnt)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));
	if (atob_exit_util(ahead, bhead, size, args))
		return ;
	init_args(args, ahead, size);
	while (size--)
	{
		if (ahead->next->data >= args->two_third)
			args->ra = ra_util(ahead, args->ra);
		else
			atob_util(ahead, bhead, args);
	}
	while (cnt < args->ra && cnt < args->rb)
		cnt = rrr_util(ahead, bhead, cnt);
	while (cnt < args->ra)
		cnt = rra_util(ahead, cnt);
	while (cnt < args->rb)
		cnt = rrb_util(ahead, bhead, cnt);
	atob(ahead, bhead, args->ra, 0);
	btoa(ahead, bhead, args->rb, 0);
	btoa(ahead, bhead, args->pb - args->rb, 0);
	free(args);
}

void	btoa(t_node *ahead, t_node *bhead, int size, int cnt)
{
	t_brgs	*brgs;

	brgs = (t_brgs *)malloc(sizeof(t_brgs));
	if (btoa_exit_util(ahead, bhead, size, brgs))
		return ;
	init_brgs(brgs, bhead, size);
	while (size--)
	{
		if (bhead->next->data < brgs->one_third)
			brgs->rb = rb_util(ahead, bhead, brgs->rb);
		else
			btoa_util(ahead, bhead, brgs);
	}
	atob(ahead, bhead, brgs->pa - brgs->ra, 0);
	while (cnt < brgs->ra && cnt < brgs->rb)
		cnt = rrr_util(ahead, bhead, cnt);
	while (cnt < brgs->ra)
		cnt = rra_util(ahead, cnt);
	while (cnt < brgs->rb)
		cnt = rrb_util(ahead, bhead, cnt);
	atob(ahead, bhead, brgs->ra, 0);
	btoa(ahead, bhead, brgs->rb, 0);
	free(brgs);
}
