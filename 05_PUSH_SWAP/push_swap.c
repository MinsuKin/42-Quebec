/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 15:59:20 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void print_list(t_node *phead) {
	t_node *p;
    printf("%d | ", phead->data);
	for (p = phead->next; p != phead; p = p->next) {
		printf("%d | ", p->data);
	}
	printf("%d | ", p->data);
	printf("\n");
}


void	ft_pushswap(t_node *a, t_node *b, int size)
{
	if (size == 2)
		ft_two(a);
	else if (size == 3)
		ft_three(a);
	else if (size == 4)
		ft_four(a, b);
	else if (size == 5)
		ft_five(a, b);
	else
		atob(a, b, size, 0);
}

int	lets_free(t_node *a, t_node *b)
{
	ft_free(a);
	ft_free(b);
	free(a);
	free(b);
	return (0);
}

int	main(int ac, char **av)
{
	int		size;
	t_node	*a;
	t_node	*b;

	a = (t_node *)malloc(sizeof(t_node));
	b = (t_node *)malloc(sizeof(t_node));
	init(a);
	init(b);
	size = make_stack(ac, av, a, 0);
	if (size == 0 || check_sorted(a, size, 0))
		return (lets_free(a, b));
	ft_pushswap(a, b, size);
	print_cmd(a, 0);
	a->data = 0;

	// print_list(a);
	// print_list(b);

	return (lets_free(a, b));
}
