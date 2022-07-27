SRCS		=	$(wildcard test_*.c)

OBJS		=	${SRCS:.c=.o}

NAME		=	testsuite.a

PROGRAM		=	executable

CC			=	gcc

CFLAGS		=	-lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include

#--- Colours ---#
RED 		=	\033[0;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[0;33m
NC 			=	\033[0m
#--- ||||||| ---#

RM			=	rm -Rf

${NAME}:		${OBJS}
				@make -C ../
				cp ../*.a ./lib${NAME}


all:			${NAME}

# ./${PROGRAM} | grep failure;
run_tests:		${NAME}
				clear
				@echo "${GREEN}--- Running Test Suite ---${NC}"
				@for i in ${SRCS}; do\
					echo "${YELLOW}--- Running" $$i "---${NC}"; \
					${CC} ${CFLAGS} $$i -L. -l$(basename ${NAME}) -lreadline -o ${PROGRAM};\
					./${PROGRAM};\
				done

clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${PROGRAM} ./lib${NAME} $(wildcard *.dSYM)

re:				fclean all

.PHONY:			all clean fclean re bonus .PHONY