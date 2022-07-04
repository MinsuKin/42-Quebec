/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:30:08 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *ft_echo_line(char *line) // check if args exist
{
    if (!*line)
        return NULL;
    while (ft_isspace(*line))
        line++;
    if (!*line)
        return NULL;
    return (line);
}

char    *ft_echo_check_option(char *line, int *newline)
{
    int len;
    int n;

    n = 0;
    len = ft_strlen(line);
    if (len >= 2 && ft_strncmp("-n", line, 2) == 0) // check if there is "-n" option (removing newline)
    {
        line += 2;
        *newline = 1;
        while (*line == 'n') // take care of "echo -nnnnnnnnn"
        {
            line++;
            n++;
        }
        if (*line && !ft_isspace(*line)) // if option is not valid, take as args
        {
            line -= n;
            line -= 2;
            *newline = 0;
        }
    }
    return (line);
}

void    ft_echo_print(char *line, int newline)
{
    if (newline)
        printf("%s", line);
    else
        printf("%s\n", line);
}

int echo_exe(char *line)
{
    int newline;

    line += 4;
    if (*line && !ft_isspace(*line))
        return print_and_return("Error: command not found\n");
    line = ft_echo_line(line); // check if args exist
    if (line == NULL)
        return print_and_return("\n"); // if no args, print newline
    newline = 0;
    line = ft_echo_check_option(line, &newline); // check if "-n" option exists
    while (ft_isspace(*line)) // white space skip
        line++;
    if (!*line && newline == 1) // if "-n" option is valid, but there is no args, print nothing
        return (0);
    ft_echo_print(line, newline); // print
    return (0);
}
