/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:30:08 by minkim            #+#    #+#             */
/*   Updated: 2022/08/28 11:02:02 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_check_option(char *line, int *newline)
{
	int	len;
	int	n;

	n = 0;
	len = ft_strlen(line);
	if (len >= 2 && ft_strncmp("-n", line, 2) == 0)
	{
		line += 2;
		*newline = 1;
		while (*line == 'n')
		{
			line++;
			n++;
		}
		if (*line && !ft_isspace(*line))
		{
			*newline = 0;
			return (0);
		}
	}
	else
		return (0);
	return (1);
}

void	ft_echo_print(t_command *command, int newline, int option)
{
	int	i;

	i = 1;
	if (option == 1)
		i = 2;
	while (command->arguments[i])
	{
		printf("%s", command->arguments[i]);
		i++;
		if (command->arguments[i])
			printf(" ");
	}
	if (newline == 0)
		printf("\n");
}

int	echo_exe(t_command *command)
{
	int		newline;
	char	*line;
	int		option;

	line = command->command;
	line += 4;
	if (command->arguments[1] == NULL)
		return (print_and_return("\n"));
	newline = 0;
	option = ft_echo_check_option(command->arguments[1], &newline);
	if (option == 1 && newline == 1 && !(command->arguments[2]))
		return (0);
	ft_echo_print(command, newline, option);
	return (0);
}
