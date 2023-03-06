#include "./inc/minishell.h"

extern t_data data;

int ft_init(char **env, t_data *data)
{
	data->sep = "|";
	data->envp = env;
	data->hd = 0;
	data->pwd = getcwd(NULL, 0);
	data->oldpwd = getcwd(NULL, 0);
	data->pip.fd_in = 0;
	data->pip.last_id = -1;
	data->pip.fd_out = 1;
	data->pip.hd_in = 0;
	ft_init_pipex_pipe(data);
	ft_create_env(env, data);
	return (0);
}