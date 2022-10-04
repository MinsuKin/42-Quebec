/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:56:21 by minkim            #+#    #+#             */
/*   Updated: 2022/09/11 18:55:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	run_builtin(t_command *command)
{
	char	*line;

	line = command->command;
	if (ft_strlen(line) == 2 && ft_strncmp("cd", line, 2) == 0)
		cd_exe(command);
	else if (ft_strlen(line) == 3 && ft_strncmp("pwd", line, 3) == 0)
		pwd_exe(line);
	else if (ft_strlen(line) == 4 && ft_strncmp("exit", line, 4) == 0)
		exit_exe(command);
	else if (ft_strlen(line) == 4 && ft_strncmp("echo", line, 4) == 0)
		echo_exe(command);
	else if (ft_strlen(line) == 3 && ft_strncmp("env", line, 3) == 0)
		env_exe(command);
	else if (ft_strlen(line) == 6 && ft_strncmp("export", line, 6) == 0)
		export_exe(command);
	else if (ft_strlen(line) == 5 && ft_strncmp("unset", line, 5) == 0)
		unset_exe(command);
	else
		return (1);
	return (0);
}

int	run_builtin2(t_command *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(command->input, STDIN_FILENO);
		dup2(command->output, STDOUT_FILENO);
		run_builtin(command);
		exit(EXIT_SUCCESS);
	}
	command->table->pid = pid;
	wait_child(command->table->pid);
	close(command->pipe[WRITE_END]);
	return (0);
}

int	builtin_check(char *cmd)
{
	char	**array;
	int		exit_code;
	int		i;

	if (!cmd)
		return (1);
	array = ft_split("cd echo env exit export unset pwd", ' ');
	i = 0;
	exit_code = 1;
	while (array[i])
	{
		if (ft_strncmp(cmd, array[i], ft_strlen(cmd)) == 0 && \
						ft_strlen(cmd) == ft_strlen(array[i]))
		{
			exit_code = 0;
			break ;
		}
		i++;
	}
	ft_free_carray(array);
	return (exit_code);
}
