BDIR= builtin
PDIR= parse
EDIR= execute

BUILTINS=		builtin_util.c		\
				exit.c				\
				exit_util.c			\
				echo.c				\
				echo.c				\
				export_util2.c		\
				export_util.c		\
				export.c			\
				env.c				\
				unset.c				\
				pwd.c				\
				cd.c				

EXECUTION=		copy_env.c			\
				execute.c			\
				bin_util.c			\
				run_builtin.c		\
				run_from_bin.c		

PARSING=		lexer.c				\
				assignation.c		\
				redirection.c		\
				tokenizer.c			\
				expansion.c

BUILTIN= $(addprefix $(BDIR)/, $(BUILTINS)) 
EXECUTE= $(addprefix $(EDIR)/, $(EXECUTION)) 
PARSE= $(addprefix $(PDIR)/, $(PARSING)) 

OBJS= $(BUILTIN:.c=.o) $(EXECUTE:.c=.o) $(PARSE:.c=.o) 

NAME		=	libminishell.a

PROGRAM		=	minishell

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -g

COMPILE_FLAGS	= -lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include

RM			=	rm -Rf

${NAME}:		${OBJS} readline.c main.c
				@make -C libft/
				cp libft/libft.a ${NAME}
				ar rcs ${NAME} ${OBJS}
				${CC} ${CFLAGS} $(COMPILE_FLAGS) readline.c main.c -L. -lminishell -o ${PROGRAM}

all:			${NAME} 

clean:
				${RM} ${OBJS}

fclean:			clean
				@make fclean -C libft/
				@make fclean -C tests/
				${RM} ${NAME} ${PROGRAM}

re:				fclean all

# Running this calls the tests Makefile which runs each .c test file
# currently in the tests directory.
run_tests:		${NAME}
				make run_tests -C tests/

.PHONY:			all clean fclean re bonus .PHONY run_tests
