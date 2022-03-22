# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 08:04:53 by msauvage          #+#    #+#              #
#    Updated: 2021/03/01 10:26:21 by msauvage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

SRCS = ${wildcard ./srcs/*.c}

OBJS = ${SRCS:.c=.o}

INCL = ${wildcard *.h}

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : ${OBJS}
	${CC} -o ${NAME} ${OBJS}

${NAME} : all

clean :
	rm -f srcs/*.o
	rm -f *.o

fclean : clean
	rm -f ${NAME}

re : fclean all
