/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/22 20:23:45 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_arg
{
	char *infile;
	char *outfile;
	char *cmd_envp;
}	t_arg;

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (s2)
		ft_strcpy(s2, s1);
	return (s2);
}

int	arg_init(int argc, char **argv, char **envp, t_arg **arg)
{
	if (argc < 5)
		return (IS_ERROR);
	(*arg) = (t_arg *)malloc(sizeof(t_arg));
	if ((*arg) == NULL)
		return (IS_ERROR);
	(*arg)->infile = ft_strdup(argv[1]);
	(*arg)->outfile = ft_strdup(argv[argc - 1]);
	if (((*arg)->infile == NULL) || ((*arg)->outfile == NULL))
		return (IS_ERROR);
	printf("%s\n", (*arg)->infile);
	printf("%s\n", (*arg)->outfile);
	printf("%s\n", envp[5]);
	// if ((parse_envp_path(&((*arg)->cmd_envp), envp)) == IS_ERROR)
	// 	return (IS_ERROR);
	// if ((parse_argv(argv, *arg)) == IS_ERROR)
	// 	return (IS_ERROR);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	*arg;

	// arg = (t_arg *)malloc(sizeof(t_arg));
	if ((arg_init(argc, argv, envp, &arg)) == IS_ERROR)
		return 0; //ft_exit(NULL, 1);
	return (0);
}
