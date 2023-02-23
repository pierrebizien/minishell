#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **argv, char **envp, int ac)
{
	data.ac = ac;
	data.av = argv;
	data.pip.in_fd = 0; 
	data.pip.out_fd = 1; 
	data.sep = "|";
	ft_create_env(envp);
	return (0);
}