#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **env, t_data *data)
{
	data->sep = "|";
	data->envp = env;
	data->hd = 0;
	data->pwd = getcwd(NULL, 0);
	data->oldpwd = getcwd(NULL, 0);
	ft_create_env(env, data);
	return (0);
}