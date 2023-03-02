# SHELL = /usr/bin/bash


LIBC =			\
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
		ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c 

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
CFLAGS = -Wall -Werror -Wextra -I ./


RED='\033[0;31m'
GREEN='\033[1;32m'
ORANGE='\033[0;33m'
YELLOW='\033[1;33m'
BLUE='\033[1;36m'
NC='\033[0m' # No Color

COLORTITOU=""

T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)

ECHOC = echo -ne "\r\033[2K"

ifndef ECHOO
ECHOO = $(ECHOC) $(COLORTITOU) "[`expr $C '*' 100 / $T`%] "
endif


vpath %.c ${SRCS_PATH}

all: 	${LIB}

${OBJS}: ${OBJS_PATH}/%.o: %.c Makefile ${SRCS_PATH}/inc/SuperLibft.h
	@	mkdir -p ${OBJS_PATH}
	@	if [ "$(shell test $C -gt 50; echo $$?)" = "0" ]; then\
       		ECHOO = $(ECHOC) $(RED) "[`expr $C '*' 100 / $T`%] ";\
		else\
       		ECHOO = $(ECHOC) $(RED) "[`expr $C '*' 100 / $T`%] ";\
    	fi
	@	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDE}

${LIB}:	${OBJS}
	$(ECHOO) $(RED) "Compiling $<"
	@	ar -rsc ${LIB} ${OBJS}
	@	$(ECHOC) $(GREEN) "$(LIB) OK"$(NC)"\n"


clean:	
	@	rm -rf ${OBJS_PATH}

fclean:	clean;
	@	rm -rf ${LIB}

re:	fclean all

.PHONY: all clean fclean re bonus