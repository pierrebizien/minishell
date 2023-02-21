#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **argv, char **envp, int ac)
{
	data.ac = ac;
	data.av = argv;
	data.envp = envp;
	fprintf(stderr, "ac = %d", data.ac);
	return (0);
}