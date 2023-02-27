#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **env)
{
	data.sep = "|";
	data.pip.infile = "/dev/stdin";
	data.pip.outfile = "/dev/stdout";
	data.envp = env;
	ft_create_env(env);
	return (0);
}