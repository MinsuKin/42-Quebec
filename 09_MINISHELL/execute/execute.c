/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:56:21 by minkim            #+#    #+#             */
/*   Updated: 2022/09/20 10:50:27 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_from_bin(t_command *command)
{
	pid_t	pid;

	if (ft_strcmp(command->command, "./minishell") == 0)
		sig_handler_minishell_recur();
	else
	{
		signal(SIGINT, sig_handler_child);
		signal(SIGQUIT, sig_handler_child);
	}
	pid = fork();
	if (pid == 0)
	{
		if (screw_this_check(command))
			exit(0);
		dup2(command->input, STDIN_FILENO);
		dup2(command->output, STDOUT_FILENO);
		close(command->pipe[READ_END]);
		bin_exe(command, g_envp);
	}
	command->table->pid = pid;
	if (command->has_redir == 0 && ft_strcmp(command->command, "cat") == 0 \
		&& command->num_args == 1)
		close(command->pipe[READ_END]);
	close(command->pipe[WRITE_END]);
	return (0);
}

void	execution_util(t_commandtable *table, int i)
{
	if (table->commands[i].has_redir)
		run_builtin2(&table->commands[i]);
	else if (table->num_commands == 1)
		run_builtin(&table->commands[i]);
	else
		run_builtin2(&table->commands[i]);
}

void	execution_open(t_commandtable *table, int i)
{
	if (table->commands[i].mode == 0)
		table->commands[i].output = open(table->commands[i].outfile_path, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (table->commands[i].mode == 1)
		table->commands[i].output = open(table->commands[i].outfile_path, \
		O_RDWR | O_CREAT | O_APPEND, 0777);
}

void	expand_command(t_command *command)
{
	int	i;

	command->command = expand(command->command, g_envp, 1);
	i = 0;
	while (command->arguments[i])
	{
		command->arguments[i] = expand(command->arguments[i], g_envp, 1);
		i++;
	}
}

void	execution(t_commandtable *table)
{
	int	i;

	if (!table)
		return ;
	i = -1;
	while (++i < table->num_commands)
	{
		expand_command(&table->commands[i]);
		execution_open(table, i);
		if (table->commands[i].command && \
				!builtin_check(table->commands[i].command))
			execution_util(table, i);
		else if (table->commands[i].command)
			run_from_bin(&table->commands[i]);
		else
		{
			i++;
			continue ;
		}
		if (table->commands[i].output != table->commands[i].pipe[WRITE_END] \
		&& table->commands[i].outfile_path != NULL)
			close(table->commands[i].output);
	}
	wait_child(table->pid);
	setting_signal();
}
