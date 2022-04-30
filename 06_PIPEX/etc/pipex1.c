/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/23 16:16:19 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_arg
{
	char *infile;
	char *outfile;
	char **cmd_envp;
	int infile_fd;
	int outfile_fd;
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	i = 0;
	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	while (i < n && (a1[i] != '\0' || a2[i] != '\0'))
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	return (0);
}

static size_t	ft_cnt_ary(const char *s, char c)
{
	size_t	cnt;
	size_t	flag;

	cnt = 0;
	flag = 0;
	while (*s != '\0')
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			cnt++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (cnt);
}

static size_t	ft_cnt_wrd(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0' && *s != c)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	char	*tmp;

	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (0);
	tmp = s2;
	while (n-- > 0)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (s2);
}

static void	ft_free(char **s, int i)
{
	while (i--)
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	wrd;
	size_t	ary;
	char	**split;

	ary = ft_cnt_ary(s, c);
	split = (char **)malloc(sizeof(char *) * (ary + 1));
	if (!split)
		return (0);
	i = -1;
	while (++i < ary)
	{
		while (*s != '\0' && *s == c)
			s++;
		wrd = ft_cnt_wrd(s, c);
		split[i] = ft_strndup(s, wrd);
		if (!split[i])
		{
			ft_free(split, i - 1);
			return (0);
		}
		s += wrd;
	}
	split[i] = NULL;
	return (split);
}

static char *find_path(char **envp)
{
    int		i;
    char	*ret_path;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp("PATH=", envp[i], 5) == 0)
        {
            ret_path = ft_strdup(envp[i] + 5);
            return (ret_path);
        }
        i++;
    }
    return (NULL);
}

int check_parse(t_arg *arg)
{
    arg->infile_fd = open(arg->infile, O_RDWR);
    if (arg->infile_fd < 0)
        return 0;//(exit_perror("not valid infile!"));
    arg->outfile_fd = open(arg->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (arg->outfile_fd < 0)
        return 0;// return (exit_perror("not valid outfile!"));
	printf("infile_fd = %d\n", arg->infile_fd);
	printf("outfile_fd = %d\n", arg->outfile_fd);
    // check_commands(arg);
    return (SUCCESS);
}

int	arg_init(int argc, char **argv, char **envp, t_arg *arg)
{
	char	*temp_path;

	if (argc < 5)
		return (ERROR);
	if (arg == NULL)
		return (ERROR);
	arg->infile = ft_strdup(argv[1]);
	arg->outfile = ft_strdup(argv[argc - 1]);
	if ((arg->infile == NULL) || (arg->outfile == NULL))
		return (ERROR);
	// printf("%s\n", arg->infile);
	// printf("%s\n", arg->outfile);
	// printf("%s\n", envp[5]);
	temp_path = find_path(envp);
	arg->cmd_envp = ft_split(temp_path, ':');
	for (int i = 0; arg->cmd_envp[i]; i++)
		printf("%s\n", arg->cmd_envp[i]);
	free(temp_path);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if ((arg_init(argc, argv, envp, arg)) == ERROR)
		return 0; //ft_exit(NULL, 1);
	check_parse(arg);
	return (0);
}
