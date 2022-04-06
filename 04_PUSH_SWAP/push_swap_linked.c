/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_linked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/05 20:42:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	n;
	int	sign;

	if (*str == 0)
		return (0);
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	n = 0;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (sign * n);
}

typedef struct	s_args
{
	long long all;
	int mid;
	int len;
	int cnt;
	int ra;
	int rb;
	int pa;
	int pb;
}				t_args;
void	init_args(t_args *args)
{
	args->all = 0;
	args->mid = 0;
	args->len = 0;
	args->cnt = 0;
	args->ra = 0;
	args->rb = 0;
	args->pa = 0;
	args->pb = 0;
}
typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
}Node;
// 이중 연결리스트 초기화
void init(Node *phead) {
	phead->prev = phead;
	phead->next = phead;
}
// 이중 연결리스트 상태 출력
void print_list(Node *phead) {
	Node *p;
    // printf("%d | ", phead->data);
	for (p = phead->next; p != phead; p = p->next) {
		printf("%d | ", p->data);
	}
	// printf("%d | ", p->data);
	printf("\n");
}
// push
void insert(Node *before, int data) {
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = data;
	newnode->prev = before;
	newnode->next = before->next;
	before->next->prev = newnode;
	before->next = newnode;
}
// pop_left
void delete(Node *head, Node *removed) {
	if (removed == head) return;
	head->next = removed->next;
	removed->next->prev = removed->prev;
	free(removed);
}
// pop
void delete_tail(Node *tail, Node *removed) {
	if (removed == tail) return;
	tail->prev = removed->prev;
	removed->prev->next = removed->next;
	free(removed);
}

// sa : swap a - 스택 a의 가장 위에 있는 두 원소(혹은 첫 번쨰 원소와 두 번째 원소)의 위치를 서로 바꾼다.
void swap_a(Node *head)
{
	int tmp;
	tmp = head->next->data;
	head->next->data = head->next->next->data;
	head->next->next->data = tmp;
	write(1, "sa\n", 3);
}
// sb : swap b - 스택 b의 가장 위에 있는 두 원소(혹은 첫 번쨰 원소와 두 번째 원소)의 위치를 서로 바꾼다.
void swap_b(Node *head)
{
	int tmp;
	tmp = head->next->data;
	head->next->data = head->next->next->data;
	head->next->next->data = tmp;
	write(1, "sb\n", 3);
}
// ss : sa와 sb를 동시에 실행한다.
void swap_ab(Node *ahead, Node *bhead)
{
	int atmp;
	int btmp;
	atmp = ahead->next->data;
	ahead->next->data = ahead->next->next->data;
	ahead->next->next->data = atmp;
	btmp = bhead->next->data;
	bhead->next->data = bhead->next->next->data;
	bhead->next->next->data = btmp;
	write(1, "ss\n", 3);
}
// pa : push a - 스택 b에서 가장 위(탑)에 있는 원소를 가져와서, 스택 a의 맨 위(탑)에 넣는다. 스택 b가 비어 있으면 아무 것도 하지 않는다.
void push_a(Node *ahead, Node *bhead)
{
	if (bhead == bhead->next) return;
	insert(ahead, bhead->next->data);
	delete(bhead, bhead->next);
	write(1, "pa\n", 3);
}
// pb : push b - 스택 a에서 가장 위(탑)에 있는 원소를 가져와서, 스택 b의 맨 위(탑)에 넣는다. 스택 a가 비어있으면 아무 것도 하지 않는다.
void push_b(Node *ahead, Node *bhead)
{
	if (ahead == ahead->next) return;
	insert(bhead, ahead->next->data);
	delete(ahead, ahead->next);
	write(1, "pb\n", 3);
}
// ra : rotate a - 스택 a의 모든 원소들을 위로 1 인덱스 만큼 올린다. 첫 번째 원소(탑)는 마지막 원소(바텀)가 된다.
void rotate_a(Node *ahead)
{
	insert(ahead->prev, ahead->next->data);
	delete(ahead, ahead->next);
	write(1, "ra\n", 3);
}
// rb : rotate b - 스택 b의 모든 원소들을 위로 1 인덱스 만큼 올린다. 첫 번째 원소(탑)는 마지막 원소(바텀)가 된다.
void rotate_b(Node *bhead)
{
	insert(bhead->prev, bhead->next->data);
	delete(bhead, bhead->next);
	write(1, "rb\n", 3);
}
// rr : ra와 rb를 동시에 실행한다.
void rotate_ab(Node *ahead, Node *bhead)
{
	insert(ahead->prev, ahead->next->data);
	delete(ahead, ahead->next);
	insert(bhead->prev, bhead->next->data);
	delete(bhead, bhead->next);
	write(1, "rr\n", 3);
}
// rra : reverse rotate a - 스택 a의 모든 원소들을 아래로 1 인덱스 만큼 내린다. 마지막 원소(바텀)는 첫 번째 원소(탑)가 된다.
void reverse_rotate_a(Node *ahead)
{
	insert(ahead, ahead->prev->data);
	delete_tail(ahead, ahead->prev);
	write(1, "rra\n", 4);
}
// rrb : reverse rotate b - 스택 b의 모든 원소들을 아래로 1 인덱스 만큼 내린다. 마지막 원소(바텀)는 첫 번째 원소(탑)가 된다.
void reverse_rotate_b(Node *bhead)
{
	insert(bhead, bhead->prev->data);
	delete_tail(bhead, bhead->prev);
	write(1, "rrb\n", 4);
}
// rrr : rra와 rrb를 동시에 실행한다.
void reverse_rotate_ab(Node *ahead, Node *bhead)
{
	insert(ahead, ahead->prev->data);
	delete_tail(ahead, ahead->prev);
	insert(bhead, bhead->prev->data);
	delete_tail(bhead, bhead->prev);
	write(1, "rrr\n", 4);
}

void ft_two(Node *ahead)
{
	if (ahead->next->data > ahead->next->next->data)
		swap_a(ahead);
}

void ft_three(Node *ahead)
{
	if (ahead->next->data > ahead->next->next->data)
	{
		if (ahead->next->data > ahead->prev->data)
			rotate_a(ahead);
		if (ahead->next->data > ahead->next->next->data)	
			swap_a(ahead);
	}
	else
	{
		if (ahead->next->data > ahead->prev->data)
			reverse_rotate_a(ahead);
		else
		{
			if (ahead->next->next->data > ahead->prev->data)
			{
				swap_a(ahead);
				rotate_a(ahead);
			}
		}
	}
}

int find_sml(Node *ahead)
{
	int sml;
	Node *p;

	sml = INT_MAX;
	p = ahead->next;
	while (p != ahead)
	{
		if (sml > p->data)
		{
			sml = p->data;
		}
		p = p->next;
	}
	return sml;
}

int find_big(Node *ahead)
{
	int big;
	Node *p;

	big = INT_MIN;
	p = ahead->next;
	while (p != ahead)
	{
		if (big < p->data)
		{
			big = p->data;
		}
		p = p->next;
	}
	return big;
}

void ft_four(Node *ahead, Node *bhead)
{
	int sml;

	sml = find_sml(ahead);
	while (1)
	{
		if (ahead->next->data == sml)
		{
			push_b(ahead, bhead);
			break;
		}
		rotate_a(ahead);
	}
	ft_three(ahead);
	push_a(ahead, bhead);
}

void ft_five(Node *ahead, Node *bhead, t_args *args)
{
	int sml;
	int big;

	sml = find_sml(ahead);
	big = find_big(ahead);
	args->cnt = 0;
	while (args->cnt != 2)
	{
		if (ahead->next->data == sml || ahead->next->data == big)
		{
			push_b(ahead, bhead);
			args->cnt++;
		}
		if (ahead->next->data == sml || ahead->next->data == big)
		{
			push_b(ahead, bhead);
			args->cnt++;
		}
		if (args->cnt == 2)
			break;
		rotate_a(ahead);
	}
	ft_three(ahead);
	push_a(ahead, bhead);
	if (bhead->next->data == big)
	{
		push_a(ahead, bhead);
		rotate_a(ahead);
	}
	else
	{
		rotate_a(ahead);
		push_a(ahead, bhead);
	}
}

void atob(Node *ahead, Node *bhead, t_args *args);
void btoa(Node *ahead, Node *bhead, t_args *args);

void atob(Node *ahead, Node *bhead, t_args *args)
{
	if (args->len <= 5)
	{
		if (args->len == 2)
			ft_two(ahead);
		else if (args->len == 3)
			ft_three(ahead);
		else if (args->len == 4)
			ft_four(ahead, bhead);
		else if (args->len == 5)
			ft_five(ahead, bhead, args);
		return;
	}
	args->cnt = 0;
	while (args->cnt < args->len)
	{
		if (ahead->next->data > args->mid)
		{
			rotate_a(ahead);
			args->ra++;
		}
		else
		{
			push_b(ahead, bhead);
			args->pb++;
		}
		args->cnt++;
	}
	args->cnt = 0;
	while (args->cnt < args->ra)
	{
		reverse_rotate_a(ahead);
		args->cnt++;
	}
	args->mid = ahead->prev->data;
	args->len = args->ra;
	args->ra = 0;
	atob(ahead, bhead, args);
	args->len = args->pb;
	args->pb = 0;
	btoa(ahead, bhead, args);
}

void btoa(Node *ahead, Node *bhead, t_args *args)
{
	if (args->len <= 2)
	{
		ft_two(ahead);
		return;
	}
	args->cnt = 0;
	while (args->cnt < args->len)
	{
		if (bhead->next->data < bhead->prev->data)
		{
			rotate_b(bhead);
			args->rb++;
		}
		else
		{
			push_a(ahead, bhead);
			args->pa++;
		}
		args->cnt++;
	}
	args->cnt = 0;
	while (args->cnt < args->rb)
	{
		reverse_rotate_b(bhead);
		args->cnt++;
	}
	args->len = args->pa;
	args->pa = 0;
	atob(ahead, bhead, args);
	args->len = args->rb;
	args->rb = 0;
	btoa(ahead, bhead, args);
}

void ft_sorted(Node *ahead, Node *bhead, t_args *args)
{
	atob(ahead, bhead, args);
}

// 메인
int		main(int ac, char **av)
{
    int i;
    t_args *args = (t_args *)malloc(sizeof(t_args));
    Node *ahead = (Node *)malloc(sizeof(Node));
    Node *bhead = (Node *)malloc(sizeof(Node));
    
    init(ahead);
    init(bhead);
    init_args(args);

    i = 1;

    while (i < ac)
    {
        insert(ahead->prev, ft_atoi(av[i]));
		args->all = args->all + ft_atoi(av[i]);
        i++;
        args->len++;
    }
	
	// 중간값 구하기
	args->mid = args->all / args->len;
	// printf("%d\n", args->sml);

    if (args->len == 2)
		ft_two(ahead);
	else if (args->len == 3)
		ft_three(ahead);
	else if (args->len == 4)
		ft_four(ahead, bhead);
	else if (args->len == 5)
		ft_five(ahead, bhead, args);
	else
		ft_sorted(ahead, bhead, args);
    
	print_list(ahead);
	print_list(bhead);

    free(ahead);
    free(bhead);
	return (0);
}
