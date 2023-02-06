#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re

HIDE =


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
INCLUDE	=	-I $(INCDIR)
LIBS	=	-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
RM		=	rm -f

# Output file name
NAME	=	cub3D

# Sources are all .c files
SRCDIR	=	src/
SRCS	=	src/array.c			\
			src/camera.c		\
			src/controls.c		\
			src/data.c			\
			src/exit_error.c	\
			src/ft_atoi.c		\
			src/ft_split.c		\
			src/ft_strchr.c		\
			src/ft_strdup.c		\
			src/ft_strjoin.c	\
			src/ft_strlcpy.c	\
			src/ft_strlen.c		\
			src/ft_strncmp.c	\
			src/ft_strpop.c		\
			src/ft_substr.c		\
			src/gnl.c			\
			src/main.c			\
			src/map_check.c		\
			src/map_check2.c	\
			src/map_check3.c	\
			src/map_check4.c	\
			src/moves.c			\
			src/parsing.c		\
			src/parsing2.c		\
			src/parsing3.c		\
			src/pixel_put.c		\
			src/render_frame.c	\
			src/render_util.c	\
			src/str_append.c	\
			src/textures.c		\
			src/xalloc.c		\
			src/check_numbers.c	

# Objects are all .o files
OBJDIR	=	bin/
OBJS	=	$(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

# Includes are all .h files
INCDIR	=	include/
INC		=	$(wildcard $(INCDIR)*.h)


#------------------------------------------------------------------------------#
#                                 TARGETS                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

# Generates output file
$(NAME): $(OBJS)
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(LIBS) $^

# Compiles sources into objects
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# Creates directory for binaries
$(OBJDIR):
	$(HIDE)mkdir -p $@

# Removes objects
clean:
	$(HIDE)$(RM) $(OBJS)

# Removes objects and executables
fclean: clean
	$(HIDE)$(RM) $(NAME)

# Removes objects and executables and remakes
re: fclean all

test: all
	$(HIDE)clear
	$(HIDE)./$(NAME) ./assets/maps/basic_map.cub
