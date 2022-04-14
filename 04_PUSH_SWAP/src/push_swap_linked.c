/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/11 22:00:17 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "push_swap.h"

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

int	ft_isalpha(int c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
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
void ft_free(Node *phead)
{
	Node *p;
	p = phead->next;
	while (p != phead) 
	{
		p = p->next;
		free(p->prev);
	}
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
		if (ahead->next->data > ahead->next->next->next->data)
			rotate_a(ahead);
		if (ahead->next->data > ahead->next->next->data)	
			swap_a(ahead);
	}
	else
	{
		if (ahead->next->data > ahead->next->next->next->data)
			reverse_rotate_a(ahead);
		else
		{
			if (ahead->next->next->data > ahead->next->next->next->data)
			{
				swap_a(ahead);
				rotate_a(ahead);
			}
		}
	}
}

int find_sml(Node *ahead, int size)
{
	int cnt;
	int sml;
	Node *p;

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
	return sml;
}

int find_big(Node *ahead, int size)
{
	int cnt;
	int big;
	Node *p;

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
	return big;
}

int find_mid(Node *ahead, int size)
{
	int cnt;
	int all;
	Node *p;

	cnt = 0;
	all = 0;
	p = ahead->next;
	while (cnt < size)
	{
		all += p->data;
		p = p->next;
		cnt++;
	}
	return all / size;
}

void ft_four(Node *ahead, Node *bhead)
{
	int sml;

	sml = find_sml(ahead, 4);
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

void ft_five(Node *ahead, Node *bhead)
{
	int cnt;
	int sml;
	int big;

	sml = find_sml(ahead, 5);
	big = find_big(ahead, 5);
	cnt = 0;
	while (cnt != 2)
	{
		if (ahead->next->data == sml || ahead->next->data == big)
		{
			push_b(ahead, bhead);
			cnt++;
		}
		if (ahead->next->data == sml || ahead->next->data == big)
		{
			push_b(ahead, bhead);
			cnt++;
		}
		if (cnt == 2)
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

void atob(Node *ahead, Node *bhead, int size);
void btoa(Node *ahead, Node *bhead, int size);

void atob(Node *ahead, Node *bhead, int size)
{
	
	int cnt;
	int ra;
	int pb;
	int mid;
	
	if (size <= 2)
	{
		if (size == 2)
			ft_two(ahead);
		return;
	}
	ra = 0;
	pb = 0;
	cnt = 0;
	mid = find_mid(ahead, size);
	while (cnt < size)
	{
		if (ahead->next->data > mid)
		{
			rotate_a(ahead);
			ra++;
		}
		else
		{
			push_b(ahead, bhead);
			pb++;
		}
		cnt++;
	}
	cnt = 0;
	while (cnt < ra)
	{
		reverse_rotate_a(ahead);
		cnt++;
	}
	atob(ahead, bhead, ra);
	btoa(ahead, bhead, pb);
}

void btoa(Node *ahead, Node *bhead, int size)
{
	int rb;
	int pa;
	int cnt;
	int mid;

	if (size <= 2)
	{
		if (size == 1)
			push_a(ahead, bhead);
		else if (size == 2)
		{
			ft_two(bhead);
			swap_b(bhead);
			push_a(ahead, bhead);
			push_a(ahead, bhead);
		}
		return;
	}
	rb = 0;
	pa = 0;
	cnt = 0;
	mid = find_mid(bhead, size);
	while (cnt < size)
	{
		if (bhead->next->data < mid)
		{
			rotate_b(bhead);
			rb++;
		}
		else
		{
			push_a(ahead, bhead);
			pa++;
		}
		cnt++;
	}
	cnt = 0;
	while (cnt < rb)
	{
		reverse_rotate_b(bhead);
		cnt++;
	}
	atob(ahead, bhead, pa);
	btoa(ahead, bhead, rb);
}

void quickSort(int arr[], int L, int R)
{
	int left = L, right = R;
	int pivot = arr[(L + R) / 2];    // pivot 설정 (가운데) 
	int temp;
	do
	{
	while (arr[left] < pivot)    // left가 pivot보다 큰 값을 만나거나 pivot을 만날 때까지 
		left++;
	while (arr[right] > pivot)    // right가 pivot보다 작은 값을 만나거나 pivot을 만날 때까지 
		right--;
	if (left<= right)    // left가 right보다 왼쪽에 있다면 교환 
	{
		temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		/*left 오른쪽으로 한칸, right 왼쪽으로 한칸 이동*/
		left++;
		right--;
	}
	} while (left<= right);    // left가 right 보다 오른쪽에 있을 때까지 반복 

	/* recursion */
	if (L < right)
	quickSort(arr, L, right);    // 왼쪽 배열 재귀적으로 반복 

	if (left < R)
	quickSort(arr, left, R);    // 오른쪽 배열 재귀적으로 반복 
}

void ft_sorted(Node *ahead, Node *bhead, int size, int arr[])
{
	int chunk = size / 3;
	int last = size - 1;

	Node *p = ahead->next;

	int pb = 0;
	int i = 1;
	int all;
	int pbb;
	int mid;
	while (i <= 2)
	{
		all = 0;
		pbb = 0;
		while (1)
		{
			if (p->data == arr[last] || p->data == arr[0])
				rotate_a(ahead);
			else if (p->data < arr[chunk * i])
			{
				all += ahead->next->data;
				push_b(ahead, bhead);
				pb++;
				pbb++;
			}
			else
				rotate_a(ahead);
			p = p->next;
			if (pb == chunk * i - 1)
				break;
		}
		mid = all / pbb;
		while (pbb--)
		{
			if (bhead->next->data < mid)
				rotate_b(bhead);
		}
		i++;
	}
	// while (1)
	// {
	// 	if (p->data == arr[last] || p->data == arr[0])
	// 		rotate_a(ahead);
	// 	else if (p->data < arr[last])
	// 	{
	// 		push_b(ahead, bhead);
	// 		pb++;
	// 	}
	// 	else
	// 		rotate_a(ahead);
	// 	p = p->next;
	// 	if (pb == last - 1)
	// 		break;
	// }
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
			if (ft_isdigit(av[i][j]) || av[i][j] == '-')
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

	int arr[size];
	Node *p = a->next;

	i = 0;
	while (i < size)
	{
		arr[i] = p->data;
		i++;
		p = p->next;
	}

	quickSort(arr, 0, size-1);

	// i = 0;
	// while(arr[i])
	// {
	// 	printf("%d ", arr[i]);
	// 	i++;
	// }
	// printf("\n");
	
    if (size == 2)
		ft_two(a);
	else if (size == 3)
		ft_three(a);
	else if (size == 4)
		ft_four(a, b);
	else if (size == 5)
		ft_five(a, b);
	else
		ft_sorted(a, b, size, arr);
    

	print_list(a);
	print_list(b);

	ft_free(a);
	ft_free(b);

    free(a);
    free(b);
	return (0);
}
