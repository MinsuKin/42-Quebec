# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 15:55:42 by minkim            #+#    #+#              #
#    Updated: 2022/04/13 18:40:22 by minkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
HEADER = push_swap.h
CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -f

SRCS = $(wildcard *.c)
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