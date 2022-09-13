/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:47:09 by minkim            #+#    #+#             */
/*   Updated: 2022/09/06 11:19:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit_code(const char *str)
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

void	ft_exit_error(t_commandtable *table)
{
	printf("exit\n");
	printf("Error: numeric argument required\n");
	free_commandtable(table);
	ft_free_carray(g_envp);
	exit(255);
}

int	ft_exit_valid(t_command *command, int exit_code)
{
	int		check_sign;
	char	*line;

	line = command->arguments[1];
	check_sign = 0;
	while (*line)
	{
		exit_code = 1;
		if (check_sign == 0 && (*line == '-' || *line == '+'))
		{
			check_sign = 1;
			line++;
		}
		else if (ft_isdigit(*line))
			line++;
		else
			ft_exit_error(command->table);
	}
	return (exit_code);
}

void	ft_exit_n_free(t_command *command, int exit_code)
{
	if (command->table->num_commands == 1)
		printf("exit\n");
	free_commandtable(command->table);
	ft_free_carray(g_envp);
	exit(exit_code);
}

int	exit_exe(t_command *command)
{
	int		exit_code;
	char	*line;

	line = command->command;
	line += 4;
	if (*line && !ft_isspace(*line))
		return (print_and_return("Error: command not found\n"));
	exit_code = 0;
	if (command->arguments[1] == NULL)
		exit_code = 0;
	else if (command->arguments[1] != NULL)
	{
		exit_code = ft_exit_valid(command, 0);
		if (command->arguments[2] != NULL)
			return (print_and_return3("exit\nError: too many arguments\n"));
	}
	if (exit_code == 1)
	{
		if (bigger_than_llong(command->arguments[1]))
			ft_exit_error(command->table);
		exit_code = ft_exit_code(command->arguments[1]);
	}
	ft_exit_n_free(command, exit_code);
	return (0);
}
