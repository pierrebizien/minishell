#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **argv, char **envp, int ac)
{
	ft_create_env(envp);
	return (0);
}