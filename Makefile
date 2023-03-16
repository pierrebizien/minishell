SHELL = /bin/bash

SRCS = ft_utils.c 
SRCS += ft_init.c 
SRCS += ft_parsing.c 
SRCS += ft_quotes.c
SRCS += ft_free.c
SRCS += ft_logo.c
SRCS += ft_pipex.c
SRCS += ft_signal.c
SRCS += ft_split_keep.c
SRCS += ft_split_leave.c
SRCS += ft_split_lquotes.c
SRCS += main.c
SRCS += pipex_utils.c
SRCS += ft_heredoc.c
SRCS += ft_exec_built_in.c


SRCS += ft_cmd_test_buildin.c
SRCS += ft_create_env.c
SRCS += ft_cmd_env.c
SRCS += ft_cmd_echo.c
SRCS += ft_cmd_export.c
SRCS += ft_cmd_pwd.c
SRCS += ft_cmd_cd.c
SRCS += ft_cmd_unset.c
SRCS += ft_cmd_exit.c
SRCS += ft_free_env.c


# SRC_PATH += /libft/src
SRC_PATH += ./minishell_src/Build-in/
SRC_PATH += ./minishell_src/Execution/
SRC_PATH += ./minishell_src/Free/
SRC_PATH += ./minishell_src/Parsing/
SRC_PATH += ./minishell_src/Signal/
SRC_PATH += ./minishell_src/Start/
SRC_PATH += ./minishell_src/Utiles/
SRC_PATH += ./minishell_src/Other/
SRC_PATH += ./minishell_src/
# SRC_PATH += /pipex


OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./minishell_src/_Objet


HEAD_PATH += -I ./minishell_src/_Include
HEAD_PATH += -I ./libft/inc

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
# @	clear
	@	./${NAME}

valgrind: all
	valgrind --track-fds=yes --suppressions=assets/ignore_readline_leaks.supp  ./${NAME}


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




${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile minishell.h
	@	$(MAKE) --no-print-directory -s -C libft
#	 @	$(MAKE) --no-print-directory -s -C pipex
	@	mkdir -p ${OBJS_PATH}
	@	$(COLORCOMPIL)
	@	${CC} ${CFLAGS} -c $< -o $@ ${HEAD_PATH}

${NAME}:  ${OBJS}
	@	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${HEAD_PATH}
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "\t$(NAME) OK" "\033[0m" "\n"





clean:
	@	echo -ne "\r\033[2K" $(YELLOW) "Cleaning\n\n"$(NC)
	@	rm -rf ${OBJS_PATH}
	@	$(MAKE) --no-print-directory -s clean -C libft
	@	echo -ne "\r\033[2K" $(GREEN) "\tLibft cleaned\n"$(NC)


fclean: clean
	@	rm -f ${NAME}
	@	$(MAKE) --no-print-directory -s fclean -C libft
	@	echo -ne "\r\033[2K" $(GREEN) "\t$(NAME) cleaned\n"$(NC)"\n"




re: fclean
	@	echo -ne "\r\033[2K" $(YELLOW) "Rebuilding..."$(NC)"\n""\n"
# @	echo ""$(YELLOW) "\nRebuilding...\n" $(NC)
	@	$(MAKE) -s


.PHONY: re clean fclean 

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


ifndef COLORCOMPIL
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(DARKGRAY) "Compiling MiniShell" $(WHITE) "$<"; \
		fi \
	fi
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)
P = `expr $C '*' 100 / $T / 5`
endif