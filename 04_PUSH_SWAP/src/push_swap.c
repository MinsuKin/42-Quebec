/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsu <minsu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:24 by minkim            #+#    #+#             */
/*   Updated: 2022/04/01 21:00:57 by minsu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

# include <stdio.h>
# include <stdlib.h>

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

typedef struct NODE {
	int data;
	struct NODE *prev;
	struct NODE *next;
}NODE;
// 이중 연결리스트 초기화
void init(NODE *phead) {
	phead->prev = phead;
	phead->next = phead;
    phead->data = 100;
}
// 이중 연결리스트 상태 출력
void print_list(NODE *phead) {
	NODE *p;
    printf("%d | ", phead->data);
	for (p = phead->next; p != phead; p = p->next) {
		printf("%d | ", p->data);
	}
	printf("\n");
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입
void insert(NODE *before, int data) {
	NODE *newnode = (NODE*)malloc(sizeof(NODE));
	newnode->data = data;
	newnode->prev = before;
	newnode->next = before->next;
	before->next->prev = newnode;
	before->next = newnode;
}
// 노드 removed를 삭제
void delete(NODE *head, NODE *removed) {
	if (removed == head) return;
	head->next = removed->next;
	removed->next->prev = removed->prev;
	free(removed);
}
// 메인
int		main(int ac, char **av)
{
    int i;
    int len;
    NODE *head = (NODE *)malloc(sizeof(NODE));
    
    init(head);
    print_list(head);
    i = 1;
    len = 0;

    while (i < ac)
    {
        insert(head, ft_atoi(av[i]));
        print_list(head);
        i++;
        len++;
    }
    len--;
    while (len >= 0)
    {
        delete(head, head->next);
        print_list(head);
        len--;
    }
    
    free(head);
	return (0);
}
