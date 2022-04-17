/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:21 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 18:36:56 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

int		ft_atoi(const char *str);
int		ft_check_num(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);

typedef struct s_node
{
	int				data;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

void	init(t_node *phead);
void	insert(t_node *before, int data);
void	delete(t_node *head, t_node *removed);
void	delete_tail(t_node *tail, t_node *removed);
void	ft_free(t_node *phead);

void	print_prev(t_node *ahead, int cmd);
void	print_cmd(t_node *ahead, int cmd);
void	swap_a(t_node *ahead);
void	swap_b(t_node *ahead, t_node *bhead);
void	swap_ab(t_node *ahead, t_node *bhead);
void	push_a(t_node *ahead, t_node *bhead);
void	push_b(t_node *ahead, t_node *bhead);
void	rotate_a(t_node *ahead);
void	rotate_b(t_node *ahead, t_node *bhead);
void	rotate_ab(t_node *ahead, t_node *bhead);
void	reverse_rotate_a(t_node *ahead);
void	reverse_rotate_b(t_node *ahead, t_node *bhead);
void	reverse_rotate_ab(t_node *ahead, t_node *bhead);

void	ft_two(t_node *ahead);
void	ft_two_b(t_node *ahead, t_node *bhead);
void	ft_three(t_node *ahead);
void	ft_three_a(t_node *ahead, t_node *bhead);
void	ft_three_a_util(t_node *ahead, t_node *bhead);
void	ft_three_b(t_node *ahead, t_node *bhead);
void	ft_three_b_util(t_node *ahead, t_node *bhead);
void	ft_three_b_util2(t_node *ahead, t_node *bhead);
void	ft_three_b_util3(t_node *ahead, t_node *bhead);
void	ft_four(t_node *ahead, t_node *bhead);
void	ft_four_a(t_node *ahead, t_node *bhead);
void	ft_four_b(t_node *ahead, t_node *bhead);
void	ft_five(t_node *ahead, t_node *bhead);
void	ft_five_util(t_node *ahead, t_node *bhead, int big);

int		find_sml(t_node *ahead, int size);
int		find_big(t_node *ahead, int size);
int		find_mid(t_node *ahead, int size);
int		find_one_third(t_node *ahead, int size);
int		find_two_third(t_node *ahead, int size);

void	atob(t_node *ahead, t_node *bhead, int size, int cnt);
void	btoa(t_node *ahead, t_node *bhead, int size, int cnt);

void	quicksort(int arr[], int L, int R);
void	swap(int *a, int *b);
void	atob_exit(t_node *ahead, t_node *bhead, int size);
void	btoa_exit(t_node *ahead, t_node *bhead, int size);
int		rra_util(t_node *ahead, int cnt);
int		rrb_util(t_node *ahead, t_node *bhead, int cnt);
int		rrr_util(t_node *ahead, t_node *bhead, int cnt);
int		ra_util(t_node *ahead, int ra);
int		pb_util(t_node *ahead, t_node *bhead, int pb);
int		rb_util(t_node *ahead, t_node *bhead, int rb);
int		pa_util(t_node *ahead, t_node *bhead, int pa);

int		find_dup(t_node *ahead, int dup);
int		check_sorted(t_node *a, int size, int i);
int		ft_error(int i);
int		make_stack(int ac, char **av, t_node *a, int i);

void	ft_pushswap(t_node *a, t_node *b, int size);

#endif
