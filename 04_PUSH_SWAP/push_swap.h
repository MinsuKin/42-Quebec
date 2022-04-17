/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:52:21 by minkim            #+#    #+#             */
/*   Updated: 2022/04/17 13:05:20 by minkim           ###   ########.fr       */
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

typedef struct Node {
	int data;
	struct Node *prev;
	struct Node *next;
}Node;

void init(Node *phead);
void insert(Node *before, int data);
void delete(Node *head, Node *removed);
void delete_tail(Node *tail, Node *removed);
void ft_free(Node *phead);

void print_cmd(Node *ahead, int cmd);
void swap_a(Node *ahead);
void swap_b(Node *ahead, Node *bhead);
void swap_ab(Node *ahead, Node *bhead);
void push_a(Node *ahead, Node *bhead);
void push_b(Node *ahead, Node *bhead);
void rotate_a(Node *ahead);
void rotate_b(Node *ahead, Node *bhead);
void rotate_ab(Node *ahead, Node *bhead);
void reverse_rotate_a(Node *ahead);
void reverse_rotate_b(Node *ahead, Node *bhead);
void reverse_rotate_ab(Node *ahead, Node *bhead);

void ft_two(Node *ahead);
void ft_two_b(Node *ahead, Node *bhead);
void ft_three(Node *ahead);
void ft_three_a(Node *ahead, Node *bhead);
void ft_three_b(Node *ahead, Node *bhead);
void ft_four(Node *ahead, Node *bhead);
void ft_four_a(Node *ahead, Node *bhead);
void ft_four_b(Node *ahead, Node *bhead);
void ft_five(Node *ahead, Node *bhead);

int find_sml(Node *ahead, int size);
int find_big(Node *ahead, int size);
int find_mid(Node *ahead, int size);
int find_one_third(Node *ahead, int size);
int find_two_third(Node *ahead, int size);

void atob(Node *ahead, Node *bhead, int size);
void btoa(Node *ahead, Node *bhead, int size);

void quickSort(int arr[], int L, int R);
void swap(int *a, int *b);

#endif
