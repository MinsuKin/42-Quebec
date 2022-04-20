/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:39:43 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 14:28:44 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_dup(t_node *ahead, int dup)
{
	t_node	*p;

	p = ahead->next;
	while (p != ahead)
	{
		if (dup == p->data)
			return (1);
		p = p->next;
	}
	return (0);
}

int	check_sorted(t_node *a, int size, int i)
{
	int		*arr;
	t_node	*p;

	arr = malloc(sizeof(int) * size);
	p = a->next;
	while (i < size)
	{
		arr[i] = p->data;
		i++;
		p = p->next;
	}
	quicksort(arr, 0, size - 1);
	p = a->next;
	i = 0;
	while (i < size)
	{
		if (arr[i] != p->data)
			break ;
		i++;
		p = p->next;
	}
	free(arr);
	if (i != size)
		return (0);
	return (1);
}

int	ft_error(int i)
{
	write(1, "Error\n", 7);
	return (i);
}

int	make_stack_util(char **av, int i, int j)
{
	if (av[i][j] == '-')
		j++;
	while (ft_isdigit(av[i][j]))
		j++;
	while (ft_isspace(av[i][j]))
		j++;
	j--;
	return (j);
}

int	make_stack(int ac, char **av, t_node *a, int i)
{
	int	j;
	int	size;

	size = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			while (ft_isspace(av[i][j]))
				j++;
			if (ft_isdigit(av[i][j]) ||
				(av[i][j] == '-' && ft_isdigit(av[i][j + 1])))
			{
				if (ft_check_num(&av[i][j]) || find_dup(a, ft_atoi(&av[i][j])))
					return (ft_error(0));
				insert(a->prev, ft_atoi(&av[i][j]));
				size++;
				j = make_stack_util(av, i, j);
			}
			else
				return (ft_error(0));
		}
	}
	return (size);
}
