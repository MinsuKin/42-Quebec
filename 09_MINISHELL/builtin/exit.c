/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:47:09 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_code(const char *str) // ft_atoi but take care of LLONG, also returns mod value
{
	long long	is_negative;
	long long	result;

	result = 0;
	is_negative = 1;
	if ((*str == '+' || *str == '-'))
	{
		if (*str == '-')
			is_negative *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + *str - 48;
		str++;
	}
	result = (result * is_negative) % 256;
	return ((int)result);
}

void ft_exit_error(void)
{
	printf("exit\n");
	printf("Error: numeric argument required\n");
	exit(255);
}

int ft_exit_too_many_args(char *line)
{
	if (*line) // check if there is more than 2 args
	{
		printf("exit\n");
		printf("Error: too many arguments\n");
		return (1);
	}
	return (0);
}

int	ft_exit_valid(char *line, int exit_code)
{
	int check_sign;

	check_sign = 0;
	while (*line) // check if there is only number
	{
		exit_code = 1;
		if (ft_isspace(*line))
			break ;
		else if (check_sign == 0 && (*line == '-' || *line == '+'))
		{
			check_sign = 1;
			line++;
		}
		else if (ft_isdigit(*line))
			line++;
		else // if not number, error
			ft_exit_error();
	}
    while (ft_isspace(*line)) // white space skip
        line++;
	if (ft_exit_too_many_args(line)) // check if there is more than 1 args
		return (-1);
	return (exit_code);
}

int exit_exe(char *line) // "exit" | "cmd" will not exit and run "cmd"(pipe not implemented yet)
{
    int	exit_code;

    line += 4; // tmp tokenizing
    if (*line && !ft_isspace(*line)) // tmp tokenizing
    	return print_and_return("Error: command not found\n");
    while (ft_isspace(*line)) // white space skip
        line++;
	exit_code = ft_exit_valid(line, 0); // check non-numeric, count args
	if (exit_code == -1) // more than 1 args
		return (0);
	if (exit_code == 1)
	{
		if (bigger_than_llong(line)) // check if exit_code is not bigger than LLONG_MAX and MIN
			ft_exit_error();
		exit_code = ft_exit_code(line);
	}
    printf("exit\n");
	exit(exit_code);
	return (0);
}
