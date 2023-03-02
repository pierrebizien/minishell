# SHELL = /usr/bin/bash

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
# LIB += -L ./pipex -lpipex
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


NOCOLOR='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
ORANGE='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
LIGHTGRAY='\033[0;37m'

DARKGRAY='\033[1;30m'
LIGHTRED='\033[1;31m'
LIGHTGREEN='\033[1;32m'
LIGHTBLUE='\033[1;34m'
LIGHTPURPLE='\033[1;35m'
LIGHTCYAN='\033[1;36m'
YELLOW='\033[1;33m'
WHITE='\033[1;37m'

ifndef ECHO
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)

ECHOC = echo -ne "\r\033[2K"
ECHO = $(ECHOC) $(DARKGRAY) "[`expr $C '*' 100 / $T`%]"
endif



${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile minishell.h
	@	$(MAKE) --no-print-directory -s -C libft
# @	$(MAKE) --no-print-directory -s -C pipex
	@	mkdir -p ${OBJS_PATH}
	@	$(ECHO)  "Compiling" $(LIGHTGRAY) "$<"
	@	${CC} ${CFLAGS} -c $< -o $@ ${HEAD_PATH}

${NAME}:  ${OBJS}
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${HEAD_PATH}



clean:
	@	rm -rf ${OBJS_PATH}
	@	$(MAKE) --no-print-directory -s clean -C libft
	@	$(MAKE) --no-print-directory -s clean -C pipex


fclean: clean
	@	rm -f ${NAME}
	@	$(MAKE) --no-print-directory -s fclean -C libft
	@	$(MAKE) --no-print-directory -s fclean -C pipex
	@	$(ECHOC) $(GREEN) "--> $(NAME) cleaned !"$(NC)"\n"



re: fclean
	@	echo $(YELLOW) "\nRebuilding...\n" $(NC)
	@	$(MAKE) -s


.PHONY: re clean fclean 