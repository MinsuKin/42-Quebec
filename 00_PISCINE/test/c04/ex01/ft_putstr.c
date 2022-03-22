/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 11:46:37 by minkim            #+#    #+#             */
/*   Updated: 2021/02/24 11:41:24 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_putstr(char *str)
{
	int i;

		write(1 , "1", 1);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
		printf("0");
}

int main(void)
{
	ft_putstr("Test");
	return (0);
}