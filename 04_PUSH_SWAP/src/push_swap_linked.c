/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_linked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/06 20:55:24 by minkim           ###   ########.fr       */
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

void ft_five(Node *ahead, Node *bhead)
{
	int sml;
	int big;
	int cnt;

	cnt = 0;
	sml = find_sml(ahead);
	big = find_big(ahead);
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

void ft_sorted(Node *ahead, Node *bhead, int arr[], int len)
{
	int chunk = len / 3;
	int last = len - 1;

	// int chunk3 = arr[chunk*3];
	// int chunk5 = arr[len-1];

	Node *p = ahead->next;

	int pb = 0;
	while (1)
	{
		if (p->data == arr[last] || p->data == arr[0])
			rotate_a(ahead);
		else if (p->data < arr[chunk])
		{
			push_b(ahead, bhead);
			pb++;
		}
		else
			rotate_a(ahead);
		p = p->next;
		if (pb == chunk - 1)
			break;
	}
	while (1)
	{
		if (p->data == arr[last] || p->data == arr[0])
			rotate_a(ahead);
		else if (p->data < arr[chunk * 2])
		{
			push_b(ahead, bhead);
			pb++;
		}
		else
			rotate_a(ahead);
		p = p->next;
		if (pb == chunk * 2 - 1)
			break;
	}
	while (1)
	{
		if (p->data == arr[last] || p->data == arr[0])
			rotate_a(ahead);
		else if (p->data < arr[last])
		{
			push_b(ahead, bhead);
			pb++;
		}
		else
			rotate_a(ahead);
		p = p->next;
		if (pb == last - 2)
			break;
	}

}

// 메인
int		main(int ac, char **av)
{
    int i;
    int len;
    Node *ahead = (Node *)malloc(sizeof(Node));
    Node *bhead = (Node *)malloc(sizeof(Node));
	
    init(ahead);
    init(bhead);

    i = 1;
	len = 0;
	
    while (i < ac)
    {
        insert(ahead->prev, ft_atoi(av[i]));
        i++;
        len++;
    }

	int arr[len];
	Node *p = ahead->next;

	i = 0;
	while (i < len)
	{
		arr[i] = p->data;
		i++;
		p = p->next;
	}

	quickSort(arr, 0, len-1);

    if (len == 2)
		ft_two(ahead);
	else if (len == 3)
		ft_three(ahead);
	else if (len == 4)
		ft_four(ahead, bhead);
	else if (len == 5)
		ft_five(ahead, bhead);
	else
		ft_sorted(ahead, bhead, arr, len);
    
	print_list(ahead);
	print_list(bhead);

    free(ahead);
    free(bhead);
	return (0);
}