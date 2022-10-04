/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 14:55:05 by minkim            #+#    #+#             */
/*   Updated: 2022/09/06 11:29:36 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd_exe(char *line)
{
	char	cwd[1024];

	line += 3;
	if (*line && !ft_isspace(*line))
		return (print_and_return("Error: command not found\n"));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		*f_exit_code() = 0;
	}
	else
	{
		perror("Error");
		*f_exit_code() = 1;
	}
	return (0);
}
