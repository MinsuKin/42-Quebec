/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:36:53 by minkim            #+#    #+#             */
/*   Updated: 2022/08/31 17:05:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_d(t_commandtable *table)
{
	if (table != NULL)
		free_commandtable(table);
	printf("\e[1A");
	printf("\e[10C");
	printf(" exit\n");
	ft_free_carray(g_envp);
	exit(EXIT_SUCCESS);
}

void	loop(char *line)
{
	t_commandtable	*table;

	add_history(line);
	table = parse(line);
	free(line);
	if (!table)
		return ;
	execution(table);
	free_commandtable(table);
	table = NULL;
}

void	minishell_loop(void)
{
	char			*line;
	struct termios	term;
	t_commandtable	*table;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	setting_signal();
	table = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			control_d(table);
		else if (*line == '\0')
			free(line);
		else
			loop(line);
		setting_signal();
	}
}

int	main(int argc, char **argv, char **envpp)
{
	(void)argc;
	(void)argv;
	*f_exit_code() = 0;
	g_envp = ft_copy_env(envpp);
	minishell_loop();
	return (0);
}
