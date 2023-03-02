

SRCS = ft_utils.c 
SRCS += ft_init.c 
SRCS += ft_parsing.c 
SRCS += ft_quotes.c
SRCS += ft_split_keep.c
SRCS += ft_free.c
SRCS += ft_logo.c
SRCS += ft_pipex.c
SRCS += ft_signal.c
SRCS += ft_split_leave.c
SRCS += main.c


SRCS += ft_cmd_test_buildin.c
SRCS += ft_create_env.c
SRCS += ft_cmd_env.c
SRCS += ft_cmd_echo.c
SRCS += ft_cmd_export.c
SRCS += ft_cmd_pwd.c
SRCS += ft_cmd_cd.c

# SRC_PATH += /libft/src
SRC_PATH = ./minishell_src/
# SRC_PATH += /pipex


OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./minishell_src/obj


HEAD_PATH += -I ./minishell_src/inc
HEAD_PATH += -I ./libft/inc
# HEAD_PATH += -I ./pipex/inc
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

valgrind: all
	valgrind ./${NAME}


RED='\033[0;31m'
GREEN='\033[1;32m'
ORANGE='\033[0;33m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)

ECHOC = echo -ne "\r\033[2K"
ECHO = $(ECHOC) $(ORANGE) "[`expr $C '*' 100 / $T`%]"
endif



${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile minishell.h
	@	$(MAKE) --no-print-directory -s -C libft
# @	$(MAKE) --no-print-directory -s -C pipex
	@	mkdir -p ${OBJS_PATH}
	@	$(ECHO) "\033[0;33m" "Compiling $<"
	@	${CC} ${CFLAGS} -c $< -o $@ ${HEAD_PATH}

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