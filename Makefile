
NAME = minishell

SRCS_MAIN = ./srcs/minishell/main.c

SRCS_GNL = ./srcs/gnl/get_next_line.c ./srcs/gnl/get_next_line_utils.c

#SRCS_PIPEX = ./srcs/pipex/ft_close.c ./srcs/pipex/ft_close2.c ./srcs/pipex/ft_close3.c ./srcs/pipex/ft_heredoc.c \
./srcs/pipex/ft_utils.c ./srcs/pipex/ft_utils2.c ./srcs/pipex/pipex.c

OBJS = ${SRCS_MAIN:.c=.o} ${SRCS_GNL:.c=.o}

GCC = cc

LIBRARY = -I. -I ./srcs/libft/ -L ./srcs/libft/ -lft -I ./srcs/gnl -I ./pipex_bonus.h

CFLAGS = -Wall -Werror -Wextra

.c.o:
	${GCC} -g ${CFLAGS} -c -I. -I ./srcs/gnl $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ./srcs/minishell/minishell.h
	$(MAKE) -C srcs/libft
	${GCC} -g -o ${NAME} ${OBJS} ${LIBRARY} 

clean:
	rm -f ${OBJS}
	$(MAKE) clean -C srcs/libft

fclean: clean
	rm -f ${NAME} ${NAME_BONUS}
	$(MAKE) fclean -C srcs/libft

re: fclean all

.PHONY: re clean fclean 