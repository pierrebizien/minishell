#include "./minishell.h"

int id2;

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
			return (NULL); //GERER LE FREE DE CEUX D AVANT
		i++;
	}
	tmp[i] = ft_strdup(src);
	if (!tmp[i])
		return (NULL); 
	i++;
	tmp[i] = 0;
	// ft_free_dchar(dest);
	dest = tmp;
	return (dest);
}

char **ft_get_paths(t_data *data)
{
    t_env *tmp;

    tmp = &data->env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)) == 0)
        {
            // fprintf(stderr, "tmp->key = |%s|\t value = |%s|\n\n", tmp->key, tmp->value);
            return (ft_split(tmp->value, ':'));
        }
        tmp = tmp->next;
    }
	return (NULL);
}

char	*find_path(char **cmd, char **paths_env)
{
	char *tmp;
	int	i;

	i = 0;
	// fprintf(stderr, "ICI 2 cmd[0] %s\n", cmd[0]);
	if (!access(cmd[0], R_OK) && (cmd[0][0] != '.' || cmd[0][0] != '/'))
	{
		if (access(cmd[0], X_OK))
			return (perror(cmd[0]), exit(errno), NULL);
		else if (cmd[0][0] != '.' && cmd[0][0] != '/')
			return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": Command not found\n", 2),\
				exit(errno), NULL);
		else
			return (ft_strdup(cmd[0]));
	}
	while (paths_env && paths_env[i])
	{
		tmp = ft_strrjoin(paths_env[i], "/", cmd[0]);
		if(!tmp)
			return (ft_putstr_fd(MALLOC_ERROR, 2), NULL);
		if (!access(tmp, F_OK))
		{
			if (access(tmp, X_OK))
				return (perror(cmd[i]), free(tmp), exit(errno), NULL);
			else
				return (tmp);
		}
		i++;
		free(tmp);
	}
	return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": Command not found\n", 2),\
		 exit(errno), NULL);
}

int	contain_token(t_exec* begin, int token, int m)
{
	int count;
	t_exec *tmp;

	tmp = begin;
	count = 0;
	while (begin && count < m)
	{
		if (begin->id == F_PIPE)
			count++;
		begin = begin->next;
	}
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == token)
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

void ft_dup_manage(t_data *data, int m)
{
	// fprintf(stderr, "ON DUP m vaut %d\n", m);
	if (contain_token(&data->exec, F_INFILE, m) || contain_token(&data->exec, F_DELIMITER, m) || !m)
	{
		// fprintf(stderr, "DUP V0\n");
		dup2(data->pip.fd_in, 0);
	}
	else if (m % 2 == 0)
	{
		// fprintf(stderr, "DUP V1\n");
		ft_close(&data->pip.pipefd2[1]);
		dup2(data->pip.pipefd2[0], 0);
		ft_close(&data->pip.pipefd2[0]);
		// ft_close(&data->pip.pipefd2[0]);
		// dup2(data->pip.pipefd2[1], 1);
		// ft_close(&data->pip.pipefd2[1]);
	}
	else
	{
		// fprintf(stderr, "DUP V2\n");
		ft_close(&data->pip.pipefd1[1]);
		dup2(data->pip.pipefd1[0], 0);
		ft_close(&data->pip.pipefd1[0]);
	}
	if (contain_token(&data->exec, F_APPEND, m) || contain_token(&data->exec, F_TRONC, m) || m == data->pip.nb_pipes)
	{
		// fprintf(stderr, "DUP V3\n");
		dup2(data->pip.fd_out, 1);
	}
	else if (m % 2 == 0)
	{
		// fprintf(stderr, "DUP V4 data pipefd1[1] = %d\n", data->pip.pipefd1[1]);
		ft_close(&data->pip.pipefd1[0]);
		dup2(data->pip.pipefd1[1], 1);
		ft_close(&data->pip.pipefd1[1]);
	}
	else if (m % 2 == 1)
	{
		// fprintf(stderr, "DUP V5\n");
		ft_close(&data->pip.pipefd2[0]);
		dup2(data->pip.pipefd2[1], 1);
		ft_close(&data->pip.pipefd2[1]);
	}
	// fprintf(stderr, "APRES DUP FD VALENT\n");
	// ft_print_fd(data);
}

void	ft_exec_cmd(t_data *data, char **cmd, int m)
{
	char **paths_env;
	char *path_exec;
	(void)cmd;

	paths_env = ft_get_paths(data);
	// perror("EXEC");
	path_exec = find_path(cmd, paths_env);
	(void)m;
	// fprintf(stderr, "ID VAUT %d \n\n\n", id2);
	ft_dup_manage(data, m);
	// dup2(data->pip.fd_in, 0);
	if (ft_test_builtin(cmd[0], data) == 1)
	{
		ft_close_all(data->pip);
		exit(data->err_built_in);
	}
	// dup2(data->pip.fd_out, 1);
	// fprintf(stderr, "avant exec out %d\n", data->pip.fd_out);
	// fprintf(stderr, "PATH EXEC VAUT %s\n", path_exec);
	execve(path_exec, cmd, paths_env);
	if (errno == 13)
	{
		ft_putstr_fd(cmd[0],2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(errno);
	}
	// fprintf(stderr, "PROBLEME D EXEC\n");
	perror("EXEC");
	exit(errno);
	// ft_print_dchar(paths_env);
	//test built-in

}

void	ft_reset_param_pip(t_data *data)
{
	data->pip.fd_in = 0;
	data->pip.fd_out = 1;
	data->pip.hd_in = 0;
}


void	ft_child_exec(t_exec *begin, t_data *data, int m)
{
	int tmp_fd;
	char **cmd;

	cmd = NULL;
	// fprintf(stderr, "test begin->str %s\n", begin->next->str);
	while (begin && begin->id != F_PIPE)
	{
	// fprintf(stderr, "test begin->str %s\n", begin->str);
		if (begin->id == F_FALSEI)
		{
			tmp_fd = open(begin->str, O_RDWR);
			if (tmp_fd == -1)
			{
				// fprintf(stderr, "HELLLO1\n");
				perror(begin->str);
				exit(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSEA)
		{
			tmp_fd = open(begin->str, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (tmp_fd == -1)
			{
				// fprintf(stderr, "HELLLO2\n");
				perror(begin->str);
				exit(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSET)
		{
			tmp_fd = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp_fd == -1)
			{
				// fprintf(stderr, "HELLLO3\n");
				perror(begin->str);
				exit(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_DELIMITER)
		{
			ft_heredoc(data, begin->str, 1);

		}
		else if (begin->id == F_FALSED)
			ft_heredoc(data, begin->str, 0);
		else if (begin->id == F_CMD)
		{
			cmd = ft_join_dstr(cmd, begin->str);
			if (!cmd)
				return ; //GERER

			// ft_print_dchar(cmd);

		}
		else if (begin->id == F_APPEND)
		{
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->pip.fd_out == -1)
			{
				// fprintf(stderr, "HELLLO4\n");
				perror(begin->str);
				exit(errno);
			}
		}
		else if (begin->id == F_TRONC)
		{
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->pip.fd_out == -1)
			{
				// fprintf(stderr, "HELLLO5\n");
				perror(begin->str);
				exit(errno);
			}
		}
			else if (begin->id == F_INFILE)
		{
			data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
			if (data->pip.fd_in == -1)
			{
				// fprintf(stderr, "HELLLO6\n");
				perror(begin->str);
				exit(errno);
			}
		}
		begin = begin->next;
		
	}
	ft_exec_cmd(data, cmd, m);
	ft_free_dchar(cmd);
}
void	ft_pipex(t_data *data)
{
	t_exec	*begin;
	int		id;
	int		m;
	// int		id;


	begin = &data->exec;
	m = 0;
	while (begin)
	{
		if (!m || m % 2 == 0)
			pipe(data->pip.pipefd1);
		else
			pipe(data->pip.pipefd2);
		id = fork();
		if (id == 0)
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
		while (wait(NULL) != -1)
			(void)begin;
		ft_close_all(data->pip);
}


//< infile << stop < TAISTE << stop cat > out -e >sexe >>bisous | < infule << stop <out ls od > test >> out -la > out

