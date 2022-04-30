/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 10:44:08 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/02/13 13:06:17 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void rush(int width, int len);
int ft_atoi(const char *str);

int main(int argc, char *argv[])
{
	if(argc == 3)
		rush(ft_atoi(argv[1]), ft_atoi(argv[2]));
	return 0;
}

int ft_atoi(const char *str)
{
	int 	result;
	int 	sign;

	result = 0;
	sign   = 1;

	if(*str)
	{
		if(*str == '-')
		{
			sign = -1;
			str++;
		}
		
		while(*str >= 48 && *str <= 57)
		{
			result = (result * 10) + (*str - 48);
			str++;
		}
		return (sign * result);
	}
	return 0;
}
