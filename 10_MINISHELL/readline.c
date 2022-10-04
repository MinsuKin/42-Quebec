/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:21:49 by minkim            #+#    #+#             */
/*   Updated: 2022/09/08 10:53:07 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
}

void	sig_handler_child(int signal)
{
	if (signal == SIGINT)
		write(1, "^C\n", 3);
	if (signal == SIGQUIT)
		write(1, "^\\Quit: 3\n", 10);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	setting_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler_minishell_recur(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
}
