NAME	= pipex

SRCS	= ${wildcard *.c}
OBJS	= ${SRCS:.c=.o}
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${OBJS} ${CFLAGS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader ${wildcard *.c} ${wildcard *.h}

.PHONY: clean fclean re all norme