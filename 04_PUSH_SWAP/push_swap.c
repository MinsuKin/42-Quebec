/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/14 18:34:28 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// 이중 연결리스트 상태 출력
void print_list(Node *phead) {
	Node *p;
    printf("%d | ", phead->data);
	for (p = phead->next; p != phead; p = p->next) {
		printf("%d | ", p->data);
	}
	printf("%d | ", p->data);
	printf("\n");
}

void ft_sorted(Node *ahead, Node *bhead, int size)
{
	atob(ahead, bhead, size);
}

// 메인
int		main(int ac, char **av)
{
    int i;
	int j;
	int size;
    Node *a = (Node *)malloc(sizeof(Node));
    Node *b = (Node *)malloc(sizeof(Node));
    
    init(a);
    init(b);

    i = 1;
	size = 0;

    while (i < ac)
    {
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '-' && !ft_isdigit(av[i][j + 1]))
			{
				write(1, "Error\n", 7);
				return (0);
			}
			if (ft_isdigit(av[i][j]) || (av[i][j] == '-' && ft_isdigit(av[i][j + 1])))
			{
				insert(a->prev, ft_atoi(&av[i][j]));
				size++;
				while (ft_isdigit(av[i][j]) || av[i][j] == '-')
					j++;
				j--;
			}
			j++;
		}
		i++;
    }

    if (size == 2)
		ft_two(a);
	else if (size == 3)
		ft_three(a);
	else if (size == 4)
		ft_four(a, b);
	else if (size == 5)
		ft_five(a, b);
	else
		ft_sorted(a, b, size);
    

	// print_list(a);
	// print_list(b);

	ft_free(a);
	ft_free(b);

    free(a);
    free(b);
	return (0);
}
