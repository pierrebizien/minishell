#include "./inc/minishell.h"

int	ft_exec_cmd_solo(t_data *data, char **cmd)
{
	char **paths_env;
	char *path_exec;
	(void)cmd;

	fprintf(stderr, "HEEHEHEHEHEHHEHEHE\n");
	paths_env = ft_get_paths(data);
	perror("EXEC");
	path_exec = find_path(cmd, paths_env);
	ft_dup_manage(data, 0);
	// dup2(data->pip.fd_in, 0);
	if (ft_test_builtin(cmd) == 1)
	{
		ft_close_all(data->pip);
		return (ft_exec_builtin(cmd, data));
	}
	else
		return (0);
}
int	ft_exec_built_in_solo(t_exec *begin, t_data *data)
{
	int tmp_fd;
	char **cmd;
	t_exec *tmp;

	cmd = NULL;
	tmp = begin;
	fprintf(stderr, "HELLO\n");
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_CMD)
		{
			cmd = ft_join_dstr(cmd, begin->str);
			if (!cmd)
				return (fprintf(stderr, "HELLO ZEBI\n"), MAL_ERCODE); //GERER
		}
		begin = begin->next;
	}
	begin = tmp;
	if (!ft_test_builtin(cmd))
		return (fprintf(stderr, "JE TM NICO ET PAS TITOU\n"), ft_free_dchar(cmd), 1);
	while (begin && begin->id != F_PIPE)
	{
	fprintf(stderr, "test begin->str %s\n", begin->str);
		if (begin->id == F_FALSEI)
		{
				fprintf(stderr, "HELLLO10\n");
			tmp_fd = open(begin->str, O_RDWR);
			if (tmp_fd == -1)
			{
				fprintf(stderr, "HELLLO1\n");
				perror(begin->str);
				return(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSEA)
		{
				fprintf(stderr, "HELLLO20\n");
			tmp_fd = open(begin->str, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (tmp_fd == -1)
			{
				fprintf(stderr, "HELLLO2\n");
				perror(begin->str);
				return(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSET)
		{
				fprintf(stderr, "HELLLO30\n");
			tmp_fd = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (tmp_fd == -1)
			{
				fprintf(stderr, "HELLLO3\n");
				perror(begin->str);
				return(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_DELIMITER)
		{
			fprintf(stderr, "HELLLO70\n");
			ft_heredoc(data, begin->str, 1);

		}
		else if (begin->id == F_FALSED)
		{
			fprintf(stderr, "HELLLO80\n");
			ft_heredoc(data, begin->str, 0);
		}
		else if (begin->id == F_APPEND)
		{
			fprintf(stderr, "HELLLO14\n");
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->pip.fd_out == -1)
			{
				fprintf(stderr, "HELLLO4\n");
				perror(begin->str);
				return(errno);
			}
		}
		else if (begin->id == F_TRONC)
		{
			fprintf(stderr, "HELLLO15\n");
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->pip.fd_out == -1)
			{
				fprintf(stderr, "HELLLO5\n");
				perror(begin->str);
				return(errno);
			}
		}
		else if (begin->id == F_INFILE)
		{
			fprintf(stderr, "HELLLO16\n");
			data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
			if (data->pip.fd_in == -1)
			{
				fprintf(stderr, "HELLLO6\n");
				perror(begin->str);
				return(errno);
			}
		}
		begin = begin->next;
		
	}
	ft_exec_cmd_solo(data, cmd);
	ft_free_dchar(cmd);
	return (0);
}