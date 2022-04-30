# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 13:45:37 by msauvage          #+#    #+#              #
#    Updated: 2021/03/04 07:58:33 by msauvage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ${wildcard ./srcs/*.c}

OBJS	= ${SRCS:.c=.o}

INCL	= include

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

NAME	= bsq

.c.o :
			${CC} -I ${INCL} ${CFLAGS} -c $< -o ${<:.c=.o}

all :		${OBJS}
			${CC} -o ${NAME} ${OBJS}

${NAME} :	all

clean :
			rm -f ${OBJS}

fclean :	clean
			rm -f ${NAME}

re :		fclean all

.PHONY :	all ${NAME} clean fclean re
