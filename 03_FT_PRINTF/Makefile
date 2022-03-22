# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 15:55:42 by minkim            #+#    #+#              #
#    Updated: 2022/01/30 15:58:31 by minkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HEADER = ft_printf.h
CFLAGS = -Wall -Wextra -Werror
CC = gcc
AR = ar rc
RM = rm -f

BSRCS = $(wildcard *lst*.c)
SRCS = $(filter-out $(BSRCS), $(wildcard *.c))
OBJS = $(SRCS:.c=.o)
BOBJS = $(BSRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: $(BOBJS) $(OBJS)
	$(AR) $(NAME) $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all