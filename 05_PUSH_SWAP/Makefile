# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 15:55:42 by minkim            #+#    #+#              #
#    Updated: 2022/04/20 19:01:40 by minkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
HEADER = push_swap.h
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

SRCS =  push_swap.c				\
		command1.c				\
		command2.c				\
		command3.c				\
		command_print.c			\
		qsort.c					\
		quicksort.c				\
		quicksort_util.c		\
		quicksort_util2.c		\
		quicksort_util3.c		\
		sort.c					\
		sort2.c					\
		sort2_util.c			\
		sort_util.c				\
		stack.c					\
		stack_util.c			\
		util.c					\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
