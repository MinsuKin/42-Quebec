/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:41:58 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 20:19:51 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_sml(t_node *ahead, int size)
{
	int		cnt;
	int		sml;
	t_node	*p;

	cnt = 0;
	sml = INT_MAX;
	p = ahead->next;
	while (cnt < size)
	{
		if (sml > p->data)
		{
			sml = p->data;
		}
		p = p->next;
		cnt++;
	}
	return (sml);
}

int	find_big(t_node *ahead, int size)
{
	int		cnt;
	int		big;
	t_node	*p;

	cnt = 0;
	big = INT_MIN;
	p = ahead->next;
	while (cnt < size)
	{
		if (big < p->data)
		{
			big = p->data;
		}
		p = p->next;
		cnt++;
	}
	return (big);
}

int	find_mid(t_node *ahead, int size)
{
	int		cnt;
	int		all;
	t_node	*p;

	cnt = 0;
	all = 0;
	p = ahead->next;
	while (cnt < size)
	{
		all += p->data;
		p = p->next;
		cnt++;
	}
	return (all / size);
}

int	find_one_third(t_node *ahead, int size)
{
	int	res;
	int	mid;
	int	sml;

	mid = find_mid(ahead, size);
	sml = find_sml(ahead, size);
	res = (mid + sml) / 2;
	return (res);
}

int	find_two_third(t_node *ahead, int size)
{
	int	res;
	int	mid;
	int	big;

	mid = find_mid(ahead, size);
	big = find_big(ahead, size);
	res = (mid + big) / 2;
	return (res);
}
