/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:35:07 by minkim            #+#    #+#             */
/*   Updated: 2021/03/01 11:05:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

int		ft_sqrt(int nb)
{
	int n;
	int i;

	n = (nb % 10);
	i = 1;
	if (n == 0 || n == 1 || n == 4 || n == 5 || n == 6 || n == 9)
	{
		while (i * i <= nb)
			i++;
		if (i * i == nb)
			return (i);
	}
	return (0);
}


int		main(void)
{
        printf("sqrt of %d is %d\n", -2576, ft_sqrt(-2576));
        printf("sqrt of %d is %d\n", 0, ft_sqrt(0));
        printf("sqrt of %d is %d\n", 1, ft_sqrt(1));
        printf("sqrt of %d is %d\n", 2, ft_sqrt(2));
        printf("sqrt of %d is %d\n", 1640045925, ft_sqrt(1640045925));
        printf("sqrt of %d is %d\n", 2147395600, ft_sqrt(2147395600));
        printf("sqrt of %d is %d\n", 2147483646, ft_sqrt(2147483646));
        printf("sqrt of %d is %d\n", 252937216, ft_sqrt(252937216));
        printf("sqrt of %d is %d\n", 1999266440, ft_sqrt(1999266440));
        printf("sqrt of %d is %d\n", 2068430400, ft_sqrt(2068430400));
        printf("sqrt of %d is %d\n", 866618250, ft_sqrt(866618250));
        printf("sqrt of %d is %d\n", 1070336656, ft_sqrt(1070336656));
        printf("sqrt of %d is %d\n", 30403578, ft_sqrt(30403578));
        printf("sqrt of %d is %d\n", 4761, ft_sqrt(4761));
        printf("sqrt of %d is %d\n", 35934310, ft_sqrt(35934310));
        printf("sqrt of %d is %d\n", 2126132100, ft_sqrt(2126132100));
        printf("sqrt of %d is %d\n", 132646863, ft_sqrt(132646863));
}
