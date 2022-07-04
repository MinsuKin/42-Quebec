/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:56:21 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pwd_exe(char *line) // "pwd" does not take args and ignore extra string if typed
{
    char    cwd[1024];

    line += 3; // tmp tokenizing
    if (*line && !ft_isspace(*line)) // tmp tokenizing
		return print_and_return("Error: command not found\n");
    if (getcwd(cwd, sizeof(cwd)) != NULL) // when "pwd" fails, it returns NULL
        printf("%s\n",cwd);
    else
        perror("Error");
	return (0);
}

int run_builtin(char *line)
{
    int len;

    len = ft_strlen(line);
    if (len >= 2 && ft_strncmp("cd", line, 2) == 0)
        cd_exe(line);
    else if (len >= 3 && ft_strncmp("pwd", line, 3) == 0)
        pwd_exe(line);
    else if (len >= 4 && ft_strncmp("exit", line, 4) == 0)
        exit_exe(line);
    else if (len >= 4 && ft_strncmp("echo", line, 4) == 0)
        echo_exe(line);
    else if (len >= 3 && ft_strncmp("env", line, 3) == 0)
        env_exe(line);
    else if (len >= 6 && ft_strncmp("export", line, 6) == 0)
        export_exe(line);
    else if (len >= 5 && ft_strncmp("unset", line, 5) == 0)
        unset_exe(line);
    else
        return (1);
    return (0);
}

int run_from_bin(char *line)
{
    pid_t	pid;

    signal(SIGINT, sig_handler_child); // to print ^C when exit from "cat / wc / grep"
    signal(SIGQUIT, sig_handler_child); // to print ^\Quit: 3 when exit from "cat / wc / grep"
    pid = fork();
    if (pid == 0)
        bin_exe(line, envp);
    waitpid(pid, 0, 0);
    return (0);
}

void    execution(char *line)
{
    int ran;

    // parsing required first
    while (ft_isspace(*line)) // tmp white space skip
        line++;
    if (!*line)
        return ;
    ran = run_builtin(line);
    if (ran)
        run_from_bin(line);
}
