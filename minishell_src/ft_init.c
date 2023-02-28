#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **env)
{
	data.sep = "|";
	data.envp = env;
	data.hd = 0;
	ft_create_env(env);
	return (0);
}