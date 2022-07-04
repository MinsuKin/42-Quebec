/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:21:08 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/02 16:42:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include "get_next_line.h"
# include "printf.h"

# define ULONG unsigned long

/*--- Macros ---*/

/*--- Structures ---*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dlist
{
	int				content;
	int				index;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef struct s_iarray
{
	int	*array;
	int	size;
}	t_iarray;

/*--- Printing ---*/
int		ft_putnchar(char c, int count);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putunbr_fd(int n, int fd);
void	ft_puthexa_fd(long n, char flag, int fd);
void	ft_putaddr_fd(long n, int prefix, int fd);

/*--- Error Management ---*/
void	ft_error(char *msg, char *file, const char *function, int line);

/*--- Character Checks ---*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isspace(int c);
int		ft_isprint(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isint(char *str);
int		ft_isnbr(char *str);

/*--- Conversions ---*/
char	*ft_itoa(int n);
ULONG	ft_atol(const char *str);
int		ft_absolute(int a);
int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_tolower(int c);

/*--- String Manipulation ---*/
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isinset(char c, char *set);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/*--- Array Manipulation ---*/
t_iarray	*ft_add_to_iarray(t_iarray *array, int insert);
int			ft_get_array_length(char **array);

/*--- Memory Manipulation ---*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);

/*--- Memory Free ---*/
void	ft_free(int argnum, ...);
void	ft_free_carray(char **array);

/*--- Linked List Functions ---*/
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*--- Double Linked List Functions ---*/
int		ft_dlstsize(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
t_dlist	*ft_dlstnew(int content);
void	ft_dlstadd_back(t_dlist **list, t_dlist *new);
void	ft_dlstadd_front(t_dlist **list, t_dlist *new);

#endif
