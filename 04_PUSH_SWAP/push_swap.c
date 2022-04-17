/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 14:44:41 by minkim           ###   ########.fr       */
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

int find_dup(Node *ahead, int dup)
{
	Node *p;

	p = ahead->next;
	while (p != ahead)
	{
		if (dup == p->data)
			return 1;
		p = p->next;
	}
	return 0;
}

int check_sorted(Node *a, int size)
{
	int i;
	int arr[size];
	Node *p;

	p = a->next;
	i = 0;
	while (i < size)
	{
		arr[i] = p->data;
		i++;
		p = p->next;
	}
	quickSort(arr, 0, size-1);
	p = a->next;
	i = 0;
	while (i < size)
	{
		if (arr[i] != p->data)
			return (0);
		i++;
		p = p->next;
	}

	return (1);
}

int ft_error()
{
	write(1, "Error\n", 7);
	return (0);
}

int make_stack(int ac, char **av, Node *a, int i)
{
	int j;
	int size;

	size = 0;
    while (++i < ac)
    {
		j = -1;
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) || (av[i][j] == '-' && ft_isdigit(av[i][j + 1])))
			{
				if (find_dup(a, ft_atoi(&av[i][j])) || ft_check_num(&av[i][j]))
					return (ft_error());
				insert(a->prev, ft_atoi(&av[i][j]));
				size++;
				while (ft_isdigit(av[i][j]) || av[i][j] == '-')
					j++;
				j--;
			}
			else
				return (ft_error());
		}
    }
	return size;
}

// 메인
int		main(int ac, char **av)
{
    int i;
	// int j;
	int size;
    Node *a = (Node *)malloc(sizeof(Node));
    Node *b = (Node *)malloc(sizeof(Node));
    
    init(a);
    init(b);

    i = 0;
	// size = 0;

	size = make_stack(ac, av, a, i);
	if (size == 0)
		return 0;

    // while (i < ac)
    // {
	// 	j = 0;
	// 	while (av[i][j])
	// 	{
	// 		if (ft_isdigit(av[i][j]) || (av[i][j] == '-' && ft_isdigit(av[i][j + 1])))
	// 		{
	// 			if (find_dup(a, ft_atoi(&av[i][j])) || ft_check_num(&av[i][j]))
	// 			{
	// 				write(1, "Error\n", 7);
	// 				return (0);
	// 			}
	// 			insert(a->prev, ft_atoi(&av[i][j]));
	// 			size++;
	// 			while (ft_isdigit(av[i][j]) || av[i][j] == '-')
	// 				j++;
	// 			j--;
	// 		}
	// 		else
	// 		{
	// 			write(1, "Error\n", 7);
	// 			return (0);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
    // }

	if (check_sorted(a, size))
		return (0);
    else if (size == 2)
		ft_two(a);
	else if (size == 3)
		ft_three(a);
	else if (size == 4)
		ft_four(a, b);
	else if (size == 5)
		ft_five(a, b);
	else
		atob(a, b, size);

	print_cmd(a, 0);
	a->data = 0;
	// print_list(a);
	// print_list(b);
	
	ft_free(a);
	ft_free(b);

    free(a);
    free(b);
	return (0);
}
