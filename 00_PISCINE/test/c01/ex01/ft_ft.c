/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 11:14:13 by minkim            #+#    #+#             */
/*   Updated: 2021/02/15 12:22:39 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_ft(int *********nbr)
{
	*********nbr = 42;
	printf("%d\n", *********nbr);
}

int		main(void)
{
	int n;
	int *i;
	int **j;
	int ***a;
	int ****b;
	int *****c;
	int ******d;
	int *******e;
	int ********f;
	int *********g;

	n = 1;
	i = &n;
	j = &i;
	a = &j;
	b = &a;
	c = &b;
	d = &c;
	e = &d;
	f = &e;
	g = &f;
	ft_ft(g);
}
