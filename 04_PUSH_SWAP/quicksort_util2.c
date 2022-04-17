/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:48:06 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 18:30:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ra_util(t_node *ahead, int ra)
{
	rotate_a(ahead);
	ra++;
	return (ra);
}

int	rb_util(t_node *ahead, t_node *bhead, int rb)
{
	rotate_b(ahead, bhead);
	rb++;
	return (rb);
}

int	pa_util(t_node *ahead, t_node *bhead, int pa)
{
	push_a(ahead, bhead);
	pa++;
	return (pa);
}

int	pb_util(t_node *ahead, t_node *bhead, int pb)
{
	push_b(ahead, bhead);
	pb++;
	return (pb);
}
