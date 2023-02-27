

SRCS =	ft_utils.c ft_cmd_echo.c  ft_cmd_export.c        ft_create_env.c  ft_init.c  ft_parsing.c  ft_quotes.c  ft_split_keep.c   \
ft_cmd_env.c   ft_cmd_test_buildin.c  ft_free.c        ft_logo.c  ft_pipex.c    ft_signal.c  ft_split_leave.c  main.c


# SRC_PATH += /libft/src
SRC_PATH = ./minishell_src/
# SRC_PATH += /pipex


OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./obj


HEAD_PATH += -I ./minishell_src/inc
HEAD_PATH += -I ./libft/inc
HEAD_PATH += -I ./pipex/inc
LIB += -L ./libft -lft
LIB += -L ./pipex -lpipex
LIB += -lreadline

NAME = minishell
CC = cc

CFLAGS += -Wall -Werror -Wextra
CFLAGS += -g


vpath %.c ${SRC_PATH}
vpath %.h ${HEAD_PATH}

all: ${NAME}

run: all
	./${NAME}



${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile minishell.h
	@	$(MAKE) --no-print-directory -s -C libft
	@	$(MAKE) --no-print-directory -s -C pipex
	@	mkdir -p ${OBJS_PATH}
		${CC} ${CFLAGS} -c $< -o $@ ${HEAD_PATH}

${NAME}:  ${OBJS}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${HEAD_PATH}



clean:
	rm -rf ${OBJS_PATH}
	$(MAKE) clean -C libft
	$(MAKE) clean -C pipex


fclean: clean
	rm -f ${NAME}
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C pipex


re: fclean all


.PHONY: re clean fclean 