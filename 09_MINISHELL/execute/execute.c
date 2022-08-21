/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:56:21 by minkim            #+#    #+#             */
/*   Updated: 2022/07/21 19:19:20 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	run_from_bin(t_command *command)
{
	pid_t	pid;

	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
	pid = fork();
	if (pid == 0)
	{
		dup2(command->input, STDIN_FILENO);
		dup2(command->output, STDOUT_FILENO);
		close(command->pipe[READ_END]);
		bin_exe(command, g_envp);
	}
	if (strcmp(command->command, "cat") == 0)
		close(command->pipe[READ_END]);
	close(command->pipe[WRITE_END]);
	return (0);
}

void	execution(t_commandtable *table)
{
	int	ran;
	int	i;

	if (!table)
		return ;
	i = 0;
	ran = 0;
	while (i < table->num_commands)
	{
		ran = builtin_check(table->commands[i].command);
		if (!ran)
		{
			if (table->num_commands == 1)
				run_builtin(&table->commands[i]);
			else
				run_builtin2(&table->commands[i]);
		}
		else
			run_from_bin(&table->commands[i]);
		i++;
	}
	while (--i)
		close(table->commands[i].input);
	wait_child();
	setting_signal();
}
