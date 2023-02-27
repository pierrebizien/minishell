#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **argv, char **envp, int ac)
{
	(void)ac;
	(void)argv;
	data.sep = "|";
	data.pip.infile = "/dev/stdin";
	data.pip.outfile = "/dev/stdout";
	data.envp = envp;
	ft_create_env(envp);
	return (0);
}