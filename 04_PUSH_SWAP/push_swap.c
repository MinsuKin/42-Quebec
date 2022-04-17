/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 17:48:56 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 이중 연결리스트 상태 출력
// void print_list(t_node *phead) {
// 	t_node *p;
//     printf("%d | ", phead->data);
// 	for (p = phead->next; p != phead; p = p->next) {
// 		printf("%d | ", p->data);
// 	}
// 	printf("%d | ", p->data);
// 	printf("\n");
// }
	// print_list(a);
	// print_list(b);

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

// 메인
int	main(int ac, char **av)
{
	int		i;
	int		size;
	t_node	*a;
	t_node	*b;

	a = (t_node *)malloc(sizeof(t_node));
	b = (t_node *)malloc(sizeof(t_node));
	init(a);
	init(b);
	i = 0;
	size = make_stack(ac, av, a, i);
	if (size == 0)
		return (0);
	if (check_sorted(a, size, 0))
		return (0);
	ft_pushswap(a, b, size);
	print_cmd(a, 0);
	a->data = 0;
	ft_free(a);
	ft_free(b);
	free(a);
	free(b);
	return (0);
}
