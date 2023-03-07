SHELL = /bin/bash


LIBC =			\
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strcmp.c

ADDITIONAL =	\
		ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_striteri.c

PRINTF =		\
		ft_printf_pc_id.c ft_printf_pc_p.c ft_printf_pc_u.c ft_printf_pc_x.c ft_printf.c

GETNEXTLINE =	\
		get_next_line_utils.c get_next_line.c

BONUS = 		\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c  \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS_PATH = ./src
SRCS = ${LIBC} ${ADDITIONAL} ${PRINTF} ${GETNEXTLINE} ${BONUS}

OBJS_PATH = ./obj
OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}

INCLUDE = -I ${SRCS_PATH}/inc

LIB = libft.a
CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I ./


vpath %.c ${SRCS_PATH}

all: 	${LIB}

${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile ${SRCS_PATH}/inc/SuperLibft.h
	@	mkdir -p ${OBJS_PATH}
	@	$(COLORCOMPIL)
	@	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDE}

${LIB}:	${OBJS}
	@	ar -rsc ${LIB} ${OBJS}
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "\t$(LIB) OK"$(NC)"\n""\n"


clean:	
	@	rm -rf ${OBJS_PATH}

fclean:	clean;
	@	rm -rf ${LIB}

re:	fclean all

.PHONY: all clean fclean re bonus


NC='\033[0m'
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
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(DARKGRAY) "Compiling Libft" $(WHITE) "$<"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(DARKGRAY) "Compiling Libft" $(WHITE) "$<"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(DARKGRAY) "Compiling Libft" $(WHITE) "$<"; \
		fi \
	fi
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)
P = `expr $C '*' 100 / $T / 5`
endif