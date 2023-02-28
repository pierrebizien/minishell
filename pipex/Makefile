SRCS = ft_redir.c ft_close2.c   ft_pip_atoi.c     ft_pip_memcmp.c      ft_pip_putstr_fd.c  ft_pip_strlen.c   get_next_line.c \
ft_close3.c   ft_pip_bzero.c    ft_pip_memcpy.c      ft_pip_split.c      ft_pip_strncmp.c  get_next_line_utils.c\
ft_close.c    ft_pip_calloc.c   ft_pip_memset.c      ft_pip_strdup.c     ft_utils2.c  \
ft_heredoc.c  ft_pip_isdigit.c  ft_pip_putendl_fd.c  ft_pip_strjoin.c    ft_utils.c pipex.c

SRCS_PATH = ./src

OBJS_PATH = ./obj
OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}

INCLUDE = -I ${SRCS_PATH}/inc

LIB = libpipex.a
CC = cc 
CFLAGS = -g -Wall -Werror -Wextra -I ./ 

vpath %.c ${SRCS_PATH}

all: 	${LIB}

${OBJS}: ${OBJS_PATH}/%.o: %.c
	@	mkdir -p ${OBJS_PATH}
	@	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDE} 

${LIB}:	${OBJS}
	@	ar -rsc ${LIB} ${OBJS}
	@	echo "\e[32mPipex OK\e[0m"

clean:	
		rm -rf ${OBJS_PATH}

fclean:	clean;
		rm -rf ${LIB}

re:	fclean all

.PHONY: all clean fclean re bonus