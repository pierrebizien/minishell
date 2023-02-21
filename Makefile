

SRCS = main.c ft_init.c ft_parsing.c ft_logo.c
# SRCS += ft_close.c ft_close2.c ft_close3.c ft_heredoc.c ft_utils.c ft_utils2.c pipex.c


# SRC_PATH += /libft/src
SRC_PATH = ./minishell_src/
# SRC_PATH += /pipex


OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./obj


HEAD_PATH += -I ./minishell_src/inc
HEAD_PATH += -I ./libft/inc
# INCLUDE += -I ./pipex/inc
LIB += -L ./libft -lft
LIB += -lreadline

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Werror -Wextra


vpath %.c ${SRC_PATH}
vpath %.h ${HEAD_PATH}

all:	${NAME}


${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile
	$(MAKE) -C libft
	mkdir -p ${OBJS_PATH}
	${CC} ${CFLAGS} -c $< -o $@ ${HEAD_PATH}

${NAME}: 	${OBJS}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${HEAD_PATH}



clean:
	rm -rf ${OBJS_PATH}
	$(MAKE) clean -C libft


fclean: clean
	rm -f ${NAME}
	$(MAKE) fclean -C libft


re: fclean all


.PHONY: re clean fclean 