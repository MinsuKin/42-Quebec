/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:21:49 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 13:27:10 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_handler_child(int signal)
{
    if (signal == SIGINT)
        write(1, "^C\n", 3);
    if (signal == SIGQUIT)
        write(1, "^\\Quit: 3\n", 10);
    if (rl_on_new_line() == -1) // send signal to readline() that met newlline and curser has moved
        exit(1);
    rl_replace_line("", 1); // clean Prompt line
}

void    sig_handler(int signal)
{
    if (signal == SIGINT)
        write(1, "\n", 1);
    if (rl_on_new_line() == -1) // send signal to readline() that met newlline and curser has moved
        exit(1);
    rl_replace_line("", 1); // clean Prompt line
    rl_redisplay();         // Prompt curser Fixed
}

void    setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
}
