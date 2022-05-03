/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:39:14 by minkim            #+#    #+#             */
/*   Updated: 2021/02/21 18:27:11 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		main(int argc, char *argv[])
{
	argc = 2;
	argv[1] = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2";
	int i;
	int j;
	int row;
	int col;
	char input[15];

	i = 0;
	j = 0;
	while (argv[1][i])
	{
		if (argv[1][i] != ' ')
		{
			input[j] = argv[1][i];
			j++;
		}
		i++;
	}
	if (argc == 2)
	{
		int numarr[4][4] = {{48, 48, 48, 48}, {48, 48, 48, 48},
		{48, 48, 48, 48}, {48, 48, 48, 48}};

		i = -1;
		while (input[++i])
		{
			if (i < 4 && input[i] == '4')
			{
				numarr[0][i] = 49;
				numarr[1][i] = 50;
				numarr[2][i] = 51;
				numarr[3][i] = 52;
			}
			else if (i < 4 && input[i] == '1')
				numarr[0][i] = 52;
			else if ((i > 3 && i < 8) && input[i] == '4')
			{
				numarr[3][i - 4] = 49;
				numarr[2][i - 4] = 50;
				numarr[1][i - 4] = 51;
				numarr[0][i - 4] = 52;
			}
			else if ((i > 3 && i < 8) && input[i] == '1')
				numarr[3][i - 4] = 52;
			else if ((i > 7 && i < 12) && input[i] == '4')
			{
				numarr[i - 8][0] = 49;
				numarr[i - 8][1] = 50;
				numarr[i - 8][2] = 51;
				numarr[i - 8][3] = 52;
			}
			else if ((i > 7 && i < 12) && input[i] == '1')
				numarr[0][i - 8] = 52;
			else if ((i > 11 && i < 16) && input[i] == '4')
			{
				numarr[i - 12][3] = 49;
				numarr[i - 12][2] = 50;
				numarr[i - 12][1] = 51;
				numarr[i - 12][0] = 52;
			}
			else if ((i > 11 && i < 16) && input[i] == '1')
				numarr[i - 12][3] = 52;
		}
		col = sizeof(numarr[0]) / sizeof(int);
		row = sizeof(numarr) / sizeof(numarr[0]);
		i = 0;
		while (i < row)
		{
			j = 0;
			while (j < col)
			{
				write(1, &numarr[i][j], 1);
				write(1, " ", 1);
				j++;
			}
			write(1, "\n", 1);
			i++;
		}
	}
}
