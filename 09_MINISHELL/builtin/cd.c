/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:37:30 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s2 || !s1)
		ft_error("invalid string pointers", __FILE__, __func__, __LINE__);
	while (s1[i] && s2[i])
	{
		if (s1[i] == '=' && s2[i] == '=')
			return (1);
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
    if (s1[i])
    {
        if (s1[i] == '=')
            return (1);
        return (0);
    }
    if (s2[i])
        return (0);
	return (1);
}

char	*ft_cd_check(char *line)
{
	char	**env;

	env = envp;
	while (*env)
	{
		if (ft_cd_strcmp(*env, line))
			return (*env);
		env++;
	}
	return (NULL);
}

char    *ft_cd_get_val(char *home)
{
    home += 4;
    if (*home == '=')
    {
        home++;
        if (*home)
            return (home);
        else
            return ("\n");
    }
    return (NULL);
}

int ft_cd_home_check(void)
{
    char    *home;
    char    *val;

    home = ft_cd_check("HOME");
    val = NULL;
    if (home != NULL)
        val = ft_cd_get_val(home); // val 있으면 리턴, 없으면 null, 비어있으면 ""
    if (val != NULL)
    {
        if (*val == '\n')
            return (0);
        if (chdir(val) != 0)
            perror("Error");
    }
    if (home == NULL || val == NULL)
        printf("Error: HOME not set\n");
    return (0);
}

int cd_exe(char *line)
{
    char *home;

    line += 2; // tmp tokenizing
    if (*line && !ft_isspace(*line))
		return print_and_return("Error: command not found\n");
    while (ft_isspace(*line)) // "cd" still runs when there is more than 1 space before the target
        line++;
    if (!*line) // no target, go home, if no HOME, error
        return (ft_cd_home_check());
    if (!*line || *line == '~') // '~' go home
    {
        home = getenv("HOME"); // need to find $HOME from "env"
        if (chdir(home) != 0)
            perror("Error");
        return (0);
    }
    home = ft_cd_strdup(line);// parsing
    if (chdir(home) != 0)
        perror("Error");
    free(home);
    home = NULL;
    return (0);
}