/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:36:53 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 14:51:36 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    control_d()
{
    printf("\e[1A"); // Push curser to a line above
    printf("\e[10C"); // Move curser to the right 10 times
    printf(" exit\n");
    // free_commandtable(table);
    exit(EXIT_SUCCESS);
}

void    minishell_loop()
{
    char *line;
    struct termios term;
    // t_commandtable *table;

    tcgetattr(STDIN_FILENO, &term); // take terminal attributes from STDIN
    term.c_lflag &= ~(ECHOCTL); // turn off the attr ECHOCTL - in local flags(a termios struct property)
    tcsetattr(STDIN_FILENO, TCSANOW, &term); // Apply changed setting
    setting_signal(); // change signal setting
    while (1)
    {
        line = readline("minishell$ ");
        if (!line)
            control_d();
        else if (*line == '\0')
            free(line);
        else
        {
            add_history(line);
            // table = parse(line);
            // print_command_table(table);
            execution(line);
            free(line);
        }
        setting_signal();
    }
}

int main(int argc, char **argv, char **envpp)
{
    (void)argc; // Werror avoid
    (void)argv; // Werror avoid
    envp = ft_copy_env(envpp); // saves in global variable
    minishell_loop();
    return (0);
}
