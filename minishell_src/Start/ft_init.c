#include "../_Include/minishell.h"

extern int err_value;

int event(void)
{ 
	return (42);
}

int ft_init(char **env, t_data *data)
{
	data->sep = "|";
	data->envp = env;
	data->hd = 0;
	data->pwd = getcwd(NULL, 0);
	data->oldpwd = getcwd(NULL, 0);
	data->pip.fd_in = 0;
	data->pip.last_id = -1;
	data->last_err_num = 0;
	data->err_built_in = 1;
	data->bool_redir_0 = 0;
	data->bool_redir_2 = 0;
	data->pip.saved_stdin = dup(0);
	data->pip.saved_stdout = dup(1);
	data->pip.fd_out = 1;
	data->pip.hd_in = 0;
	ft_init_pipex_pipe(data);
	ft_create_env(env, data);
	rl_event_hook=event;
	// FILE *none = fopen("/dev/null", "r");
	rl_outstream = stderr;
	return (0);
}