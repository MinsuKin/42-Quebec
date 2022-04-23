/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:16:36 by minkim            #+#    #+#             */
/*   Updated: 2022/04/22 20:11:49 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>

# ifndef IS_ERROR
#  define IS_ERROR -1
# endif

// size_t			ft_strlen(const char *s);
// static size_t	ft_cnt_ary(const char *s, char c);
// static size_t	ft_cnt_wrd(char const *s, char c);
// static char		*ft_strndup(const char *s1, size_t n);
// static void		ft_free(char **s, int i);
// char			**ft_split(char const *s, char c);
// char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
// int				ft_strncmp(const char *s1, const char *s2, size_t n);
// void			*ft_memset(void *b, int c, size_t len);

#endif
