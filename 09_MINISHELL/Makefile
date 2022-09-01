BDIR= builtin
PDIR= parse
EDIR= execute

BUILTINS=		builtin_util.c		\
				exit.c				\
				exit_util.c			\
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
				expansion.c			\
				heredoc.c			\
				assignation_utils.c	\
				environment_variables.c		\
				tokens.c 			\

BUILTIN= $(addprefix $(BDIR)/, $(BUILTINS)) 
EXECUTE= $(addprefix $(EDIR)/, $(EXECUTION)) 
PARSE= $(addprefix $(PDIR)/, $(PARSING)) 

OBJS= $(BUILTIN:.c=.o) $(EXECUTE:.c=.o) $(PARSE:.c=.o) 

NAME		=	libminishell.a

PROGRAM		=	minishell

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

COMPILE_FLAGS	= -lreadline -L./readline/lib -I./readline/include

RM			=	rm -Rf

${NAME}:		${OBJS} readline.c main.c
				@make -C libft/
				cp libft/libft.a ${NAME}
				ar rcs ${NAME} ${OBJS}
				${CC} ${CFLAGS} $(COMPILE_FLAGS) readline.c utils.c main.c -L. -lminishell -o ${PROGRAM}

all:			${NAME} 

clean:
				${RM} ${OBJS}
				@make clean -C libft/

fclean:			clean
				@make fclean -C libft/
				${RM} ${NAME} ${PROGRAM}

re:				fclean all

.PHONY:			all clean fclean re bonus .PHONY
