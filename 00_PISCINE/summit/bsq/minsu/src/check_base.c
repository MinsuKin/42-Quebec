/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dp.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:35:58 by minkim            #+#    #+#             */
/*   Updated: 2021/03/03 15:36:24 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	g_char_empty;
char	g_char_obstacle;
char	g_char_full;
int		g_char_row;

int		check_global(void)
{
	if (!(g_char_row) || !(g_char_empty) ||
	!(g_char_obstacle) || !(g_char_full))
		return (0);
	if (g_char_empty == g_char_obstacle)
		return (0);
	if (g_char_empty == g_char_full)
		return (0);
	if (g_char_full == g_char_obstacle)
		return (0);
	return (1);
}

int		check_row(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		check_inst(char board[][29], int row, int j, int x)
{
	if (j > 4)
	{
		while (j >= 0)
		{
			if (row - 1 == j && board[0][j] != '\n')
				return (0);
			if (row - 2 == j)
				g_char_full = board[0][j];
			if (row - 3 == j)
				g_char_obstacle = board[0][j];
			if (row - 4 == j)
				g_char_empty = board[0][j];
			if (row - 5 == j && check_row(board[0][j]))
				g_char_row = board[0][j] - '0';
			if (row - 6 >= j && check_row(board[0][j]) == 1)
			{
				g_char_row = g_char_row + ((board[0][j] - '0') * x);
				x = x * 10;
			}
			j--;
		}
	}
	else
		return (0);
	return (1);
}

int		check_map(char board[][29], int j, int k)
{
	int i;

	i = 0;
	while (board[1][i])
		i++;
	if (i == 0)
		return (0);
	j = 1;
	while (board[j][0] == g_char_empty || board[j][0] == g_char_obstacle)
	{
		k = 0;
		while (board[j][k] == g_char_empty || board[j][k] ==
		g_char_obstacle || board[j][k] == '\n')
			k++;
		if (k != i)
			return (0);
		j++;
	}
	return (1);
}

int		main(void)
{
	int		j;
	char	board[10][29] = {
		"9.ox\n",
		"...........................\n",
		"....o......................\n",
		"............o..............\n",
		"...........................\n",
		"....o......................\n",
		"...............o...........\n",
		"...........................\n",
		"......o..............o.....\n",
		"..o.......o................\n"
	};
	j = 0;
	while (board[0][j])
		j++;
	if (check_inst(board, j, j, 10) == 0 ||
	check_map(board, 1, 0) == 0 || check_global() == 0)
	{
		printf("map error\n");
		return (0);
	}
	printf("%c\n", g_char_full);
	printf("%c\n", g_char_obstacle);
	printf("%c\n", g_char_empty);
	printf("%d\n", g_char_row);
}
