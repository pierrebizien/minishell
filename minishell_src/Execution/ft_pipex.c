#include "./minishell.h"

extern int err_value;


char **ft_join_dstr(char **dest, char* src)
{
	int	i;
	char **tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_strstrlen(dest) + 2));
	if (!tmp) //GERER
		return (NULL);
	while (dest && dest[i])
	{
		tmp[i] = ft_strdup(dest[i]);
		if (!tmp[i])
			return (ft_free_dchar(tmp), NULL); //GERER LE FREE DE CEUX D AVANT
		i++;
	}
	tmp[i] = ft_strdup(src);
	if (!tmp[i])
		return (ft_free_dchar(tmp), NULL); 
	i++;
	tmp[i] = 0;
	ft_free_dchar(dest);
	return (tmp);
}

char **ft_get_paths(t_data *data, char **cmd, char **cmd_quotes)
{
    t_env *tmp;
	char **tab;

    tmp = &data->env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)) == 0)
		{
            tab = ft_split(tmp->value, ':');
			if (tab == NULL)
				return(ft_free_dchar(cmd_quotes), ft_free_dchar(cmd), ft_free_dchar(data->to_free.env_tab), ft_free_list(&data->exec), fprintf(stderr, "error 22\n"), ft_pb_malloc(data), NULL);
			return (tab);
		}
        tmp = tmp->next;
    }
	return (NULL);
}
void	ft_free_in_find_path(char **cmd, char **paths_env, t_data *data, char **cmd_quotes)
{
	ft_free_dchar(data->to_free.env_tab);
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	ft_free_dchar(paths_env);
	ft_free_env(data);
	free(data->oldpwd);
	free(data->pwd);
	ft_close_all(data->pip, data);
	ft_free_list(&data->exec);

}

char	*find_path(char **cmd, char **paths_env, t_data *data, char **cmd_quotes)
{
	char *tmp;
	int	i;
	(void)cmd_quotes;
	(void)data;

	i = 0;
	if (cmd && cmd[0] && !cmd[0][0])
		return (ft_putstr_fd(": Command not found\n", 2), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (ft_strncmp(cmd[0], ".", ft_strlen(cmd[0])) == 0 || ft_strncmp(cmd[0], "..", ft_strlen(cmd[0])) == 0)
		return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": Command not found\n", 2), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (ft_test_builtin(cmd) == 1)
		return (NULL);
	if ((cmd[0][0] == '/' || cmd[0][0] == '.') && access(cmd[0], F_OK))
		return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": No such file or directory\n", 2), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (!access(cmd[0], F_OK))
	{
		if (access(cmd[0], X_OK))
			return (perror(cmd[0]), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(126), NULL);
		else
		{
			tmp = ft_strdup(cmd[0]);
			if (tmp == NULL)
				return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), ft_putstr_fd(MALLOC_ERROR, 2),exit(MAL_ERCODE),  NULL);
			return (tmp);
		}
	}
	while (paths_env && paths_env[i])
	{
		tmp = ft_strrjoin(paths_env[i], "/", cmd[0]);
		if(!tmp)
			return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), ft_putstr_fd(MALLOC_ERROR, 2),exit(MAL_ERCODE),  NULL);
		if (!access(tmp, F_OK))
		{
			if (access(tmp, X_OK))
				return (perror(cmd[i]), free(tmp), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(126), NULL);
			else
				return (tmp);
		}
		i++;
		free(tmp);
	}
	ft_putstr_fd(cmd[0], 2);
	if (ft_strchr(cmd[0], '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Command not found\n", 2);
	return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
}
int	is_out(char *str)
{
	int	i;
	char **tmp;

	i = 0;
	if (!str || !str[0])
		return (0);
	tmp = ft_split(str, '/');
	if (!tmp)
		return (-1);
	if (ft_strncmp(tmp[0], "dev", ft_strlen(tmp[0])) == 0 && ft_strncmp(tmp[1], "stdout", ft_strlen(tmp[1])) == 0)
		return (ft_free_dchar(tmp),1);
	ft_free_dchar(tmp);
	return (0);
}
int	contain_token(t_exec* begin, int token, int m) // ET PAS STDOUT
{
	int count;
	t_exec *tmp;

	tmp = begin;
	begin = tmp;
	count = 0;
	while (begin && count < m)
	{
		if (begin->id == F_PIPE)
			count++;
		begin = begin->next;
	}
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == token && !is_out(begin->str))
			return (1);
		begin = begin->next;
	}
	begin = tmp;
	return (0);
}

void ft_print_fd(t_data *data)
{
	fprintf(stderr, "fd in %d\n", data->pip.fd_in);
	fprintf(stderr, "fd out %d\n", data->pip.fd_out);
	fprintf(stderr, "pipefd1 [0] %d\n", data->pip.pipefd1[0]);
	fprintf(stderr, "pipefd1 [1] %d\n", data->pip.pipefd1[1]);
	fprintf(stderr, "pipefd2 [0]  %d\n", data->pip.pipefd2[0]);
	fprintf(stderr, "pipefd2 [1] %d\n", data->pip.pipefd2[1]);
}

int ft_search_hd_name(t_exec *begin, int m)
{
	t_exec *tmp;
	int		fd;

	tmp = begin;
	while (m)
	{
		if (tmp->id == F_PIPE)
			m--;
		tmp = tmp->next;
	}
	while (tmp && tmp->id != F_PIPE)
	{
		if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ)
		{
			fd = open(tmp->hd_filename, O_RDONLY);
			if (fd == -1)
				return (-1); // GERER
			return (fd);
		}
		tmp = tmp->next;
	}
	return (-2);
}

void ft_dup_manage(t_data *data, int m)
{
	int tmp_fd;

	if (contain_token(&data->exec, F_DELIMITER, m) || contain_token(&data->exec, F_DELIMITER_SQ, m))
	{
		tmp_fd = ft_search_hd_name(&data->exec, m);
		dup2(tmp_fd, 0);
		ft_close(&tmp_fd);
	}
	else if (!m || contain_token(&data->exec, F_INFILE, m))
	{
		dup2(data->pip.fd_in, 0);
	}
	else if (m &&  m % 2 == 0)
	{
		ft_close(&data->pip.pipefd2[1]);
		dup2(data->pip.pipefd2[0], 0);
		ft_close(&data->pip.pipefd2[0]);

	}
	else
	{
		ft_close(&data->pip.pipefd1[1]);
		dup2(data->pip.pipefd1[0], 0);
		ft_close(&data->pip.pipefd1[0]);
	}
	if (contain_token(&data->exec, F_APPEND, m) || contain_token(&data->exec, F_TRONC, m) || m == data->pip.nb_pipes)
	{
		dup2(data->pip.fd_out, 1);
	}
	else if (!m || m % 2 == 0)
	{
		ft_close(&data->pip.pipefd1[0]);
		dup2(data->pip.pipefd1[1], 1);
		ft_close(&data->pip.pipefd1[1]);
	}
	else
	{
		ft_close(&data->pip.pipefd2[0]);
		dup2(data->pip.pipefd2[1], 1);
		ft_close(&data->pip.pipefd2[1]);
	}
}

int	ft_len_list(t_env *begin)
{
	t_env *tmp;
	int	count;

	tmp = begin;
	count = 0;
	while (begin)
	{
		count++;
		begin = begin->next;
	}
	begin = tmp;
	return (count);
}


char **ft_get_env(t_env *env)
{
	t_env *tmp;
	char **output;
	int	k;
	int count = 0;
	tmp = env;
	k = 0;
	output = malloc(sizeof(char *) * (ft_len_list(env) + 1));
	if (!output)
		return (NULL);
	output[ft_len_list(env)] = 0;
	while (env)
	{
		output[k] = malloc(sizeof(char) * (ft_strlen(env->key) + ft_strlen(env->value) + 2));
		if (!output[k])
			return (ft_free_dchar(output), NULL);
		ft_memcpy(output[k], env->key, ft_strlen(env->key));
		output[k][ft_strlen(env->key)] = '=';
		ft_memcpy(output[k] + ft_strlen(env->key) + 1, env->value, ft_strlen(env->value)  + 1);
		k++;
		env = env->next;
		count++;
	}
	env  = tmp;
	return (output);
}

void	ft_exec_cmd(t_data *data, char **cmd, int m, char **cmd_quotes)
{

	if (!contain_token(&data->exec, F_CMD, m))
		return(ft_close_all(data->pip, data), ft_free_dchar(cmd_quotes), ft_free_dchar(cmd), ft_free_env(data), free(data->oldpwd), free(data->pwd), ft_free_list(&data->exec), exit(0)); // RAJOUTE PB MALLOC
	data->to_free.env_tab = ft_get_env(&data->env); //GERER FREE ET FD SUR EXIT
	if (data->to_free.env_tab == NULL)
		return(ft_free_dchar(cmd_quotes), ft_free_dchar(cmd), ft_free_list(&data->exec), fprintf(stderr, "error 21\n"), ft_pb_malloc(data));
	data->to_free.paths_env = ft_get_paths(data, cmd, cmd_quotes); //GERER FREE ET FD SUR EXIT
	data->to_free.path_exec = find_path(cmd, data->to_free.paths_env, data, cmd_quotes); //GERER FREE ET FD SUR EXIT
	ft_dup_manage(data, m);
	if (ft_exec_builtin(cmd, data, cmd_quotes) == 1)
	{
		free(data->to_free.path_exec);
		ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
		ft_close_all(data->pip, data);
		exit(err_value);
	}
	execve(data->to_free.path_exec, cmd, data->to_free.env_tab);
	free(data->to_free.path_exec);
	if (errno == 13)
	{
		ft_putstr_fd(cmd[0],2);
		ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
	perror("");
	//CLOSE ET FREE TOUT
	exit(errno);
}

void	ft_reset_param_pip(t_data *data)
{
	data->pip.fd_in = 0;
	data->pip.fd_out = 1;
	data->pip.hd_in = 0;
}


void ft_free_child_exec(t_data *data, char **cmd, char **cmd_quotes)
{
	ft_free_dchar(cmd_quotes);
	ft_free_dchar(cmd);
	ft_free_env(data);
	free(data->oldpwd);
	free(data->pwd);
	ft_close_all(data->pip, data);
	ft_free_list(&data->exec);
}



int	ft_child_exec(t_exec *begin, t_data *data, int m)
{
	int tmp_fd;
	char **cmd;
	char **cmd_quotes;

	ft_init_sigint_exec();
	cmd = NULL;
	cmd_quotes = NULL;
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_FALSEI)
		{
			tmp_fd = open(begin->str, O_RDWR);
			if (tmp_fd == -1)
			{
				perror(begin->str);
				err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSEA)
		{
			tmp_fd = open(begin->str, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (tmp_fd == -1)
			{
				perror(begin->str);
				err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSET)
		{
			tmp_fd = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp_fd == -1)
			{
				perror(begin->str);
				err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_CMD)
		{
			cmd = ft_join_dstr(cmd, begin->str);
			if (!cmd)
			{
				ft_free_list(&data->exec);
				fprintf(stderr, "ERROR 3\n");

				ft_pb_malloc(data);
				return (MAL_ERCODE); //GERER
			}
			cmd_quotes = ft_join_dstr(cmd_quotes, begin->quotes);
			if (!cmd_quotes)
			{
				fprintf(stderr, "ERROR 4\n");

				ft_free_list(&data->exec);
				ft_pb_malloc(data);
				return (MAL_ERCODE); //GERER
			}
		}
		else if (begin->id == F_APPEND)
		{
			ft_close(&data->pip.fd_out);
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->pip.fd_out == -1)
			{
				perror(begin->str);
				err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
		}
		else if (begin->id == F_TRONC)
		{
			ft_close(&data->pip.fd_out);
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->pip.fd_out == -1)
			{
				perror(begin->str);
				err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
		}
			else if (begin->id == F_INFILE)
		{
			ft_close(&data->pip.fd_in);
			data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
			if (data->pip.fd_in == -1)
			{
				perror(begin->str);
				err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
		}
		begin = begin->next;
		
	}
	ft_exec_cmd(data, cmd, m, cmd_quotes);
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	return (0);
}

void	ft_init_in_out(t_data *data)
{
	ft_close(&data->pip.fd_in);
	ft_close(&data->pip.fd_out);
	data->pip.fd_in = dup(data->pip.saved_stdin);
	data->pip.fd_out = dup(data->pip.saved_stdout);
}
void	ft_pipex(t_data *data)
{
	t_exec	*begin;
	// int		id;
	int		m;
	// int		id;


	begin = &data->exec;
	m = 0;
	if (!data->pip.nb_pipes)
		if(ft_exec_built_in_solo(begin, data))
			return ;
	begin = &data->exec;
	while (begin)
	{
		ft_init_in_out(data);
		if (!m || m % 2 == 0)
			pipe(data->pip.pipefd1);
		else
			pipe(data->pip.pipefd2);
		signal(SIGINT, SIG_IGN);
		ft_init_sigquit_exec();
		data->pip.last_id = fork();
		if (data->pip.last_id == 0)
			ft_child_exec(begin, data, m);
		if (!m || m % 2 == 0)
		{
			ft_close(&data->pip.pipefd2[0]);
			ft_close(&data->pip.pipefd1[1]);
		}
		else
		{
			ft_close(&data->pip.pipefd1[0]);
			ft_close(&data->pip.pipefd2[1]);
		}
		while (begin && begin->id != F_PIPE)
			begin = begin->next;
		if (begin && begin->id == F_PIPE)
			begin = begin->next;
		
		m++;
	}
		// fprintf(stderr, "1err_value = %d\n\n", err_value);
		waitpid(data->pip.last_id, &err_value, 0);
		if (WIFEXITED(err_value))
			err_value = WEXITSTATUS(err_value);
		// fprintf(stderr, "2err_value = %d\n\n", err_value);
		while (wait(NULL) != -1)
			(void)begin;
		ft_close_all(data->pip, data);
}


//< infile << stop < TAISTE << stop cat > out -e >sexe >>bisous | < infule << stop <out ls od > test >> out -la > out

//