#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **env)
{
	ft_create_env(env);
	return (0);
}