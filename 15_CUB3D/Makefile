#------------------------------------------------------------------------------#
#                                  GENERICS                                    #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: test # RBS
.DELETE_ON_ERROR: $(NAME)
.PHONY: all bonus clean fclean re

HIDE =	@


#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=address
INCLUDE	=	-I $(INCDIR)
LIBS	=	-L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
RM		=	rm -f

# Output file name
NAME	=	cub3D

# Sources are all .c files
SRCDIR	=	src/
SRCS	=	$(wildcard $(SRCDIR)*.c) # Wildcard for sources is forbidden by norminette

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

val: re
	$(HIDE)clear
	$(HIDE)valgrind									\
			--leak-check=full						\
			--show-leak-kinds=all					\
			--show-reachable=yes					\
			--track-fds=yes							\
			--error-limit=no						\
			--suppressions=./config/cub3D.supp	\
			./$(NAME) ./assets/maps/basic_map.cub

test: re
	$(HIDE)clear
	$(HIDE)./$(NAME) ./assets/maps/basic_map.cub
