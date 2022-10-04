# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 12:34:31 by tgarriss          #+#    #+#              #
#    Updated: 2022/08/25 13:54:05 by tgarriss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_absolute.c		\
			ft_add_to_iarray.c	\
			ft_add_to_sarray.c	\
			ft_atoi.c		\
			ft_atol.c		\
			ft_bzero.c		\
			ft_calloc.c		\
			ft_error.c		\
			ft_free.c		\
			ft_free_carray.c	\
			ft_get_array_length.c	\
			ft_isalnum.c	\
			ft_isalpha.c	\
			ft_isascii.c	\
			ft_isdigit.c	\
			ft_isint.c		\
			ft_isinset.c	\
			ft_isinstring.c	\
			ft_isnbr.c		\
			ft_islower.c	\
			ft_isupper.c	\
			ft_isspace.c	\
			ft_isprint.c	\
			ft_itoa.c		\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_memcpy.c		\
			ft_memmove.c	\
			ft_memset.c		\
			ft_print_sarray.c	\
			ft_putchar_fd.c	\
			ft_putnchar.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_puthexa_fd.c	\
			ft_putstr_fd.c	\
			ft_putaddr_fd.c	\
			ft_split.c		\
			ft_strchr.c		\
			ft_strdup.c		\
			ft_striteri.c	\
			ft_strjoin.c	\
			ft_strlcat.c	\
			ft_strlcpy.c	\
			ft_strlen.c		\
			ft_strmapi.c	\
			ft_strcmp.c		\
			ft_strncmp.c	\
			ft_strnstr.c	\
			ft_strrchr.c	\
			ft_strtrim.c	\
			ft_substr.c		\
			ft_tolower.c	\
			ft_toupper.c	\
			ft_lstadd_back.c	\
			ft_lstadd_front.c	\
			ft_lstclear.c		\
			ft_lstdelone.c		\
			ft_lstiter.c		\
			ft_lstlast.c		\
			ft_lstnew.c			\
			ft_lstsize.c		\
			ft_lstmap.c			\
			ft_dlstadd_back.c	\
			ft_dlstadd_front.c	\
			ft_dlstsize.c		\
			ft_dlstlast.c		\
			ft_dlstnew.c		\
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			printf/ft_printf.c	\
			printf/ft_printf_utils.c	\
			printf/ft_printf_utils2.c	\


OBJS	=	${SRCS:.c=.o}

NAME	=	libft.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

HEADER	=	includes/

.c.o:
			${CC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${SRCS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} ./a.out

re:			fclean all

.PHONY:		all clean fclean re
