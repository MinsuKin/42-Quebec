/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:12:49 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/28 10:25:36 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*f_exit_code(void)
{
	static int	exit_code;

	return (&exit_code);
}

void	wait_child(void)
{
	int	status;
	int	signo;
	int	i;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			*f_exit_code() = 128 + signo;
		}
		else
			*f_exit_code() = WEXITSTATUS(status);
	}
}
