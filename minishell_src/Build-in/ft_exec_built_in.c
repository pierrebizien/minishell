#include "../_Include/minishell.h"

extern int err_value;

void	ft_free_err_mal_cmd_solo(char **cmd, char **cmd_quotes, t_data *data)
{
		ft_free_dchar(cmd);
		ft_free_dchar(cmd_quotes);
		ft_free_list(&data->exec);
		ft_pb_malloc(data);
}


int	ft_exec_cmd_solo(t_data *data, char **cmd, char **cmd_quotes)
{
	(void)cmd;

	// fprintf(stderr, "HEEHEHEHEHEHHEHEHE\n");
	// perror("EXEC");

	ft_dup_manage(data, 0);
	// dup2(data->pip.fd_in, 0);
	if (ft_test_builtin(cmd) == 1)
	{
		ft_close_all(data->pip);
		ft_exec_builtin(cmd, data, cmd_quotes);
		ft_init_in_out(data);
		// free(cmd);
		// free(cmd_quotes);
		dup2(data->pip.saved_stdin, 0);
		dup2(data->pip.saved_stdout, 1);
		return (1);
	}
	else
		return (0);
}
int	ft_exec_built_in_solo(t_exec *begin, t_data *data)
{
	int tmp_fd;
	char **cmd;
	char **cmd_quotes;
	t_exec *tmp;

	cmd = NULL;
	cmd_quotes = NULL;
	tmp = begin;
	// ft_print_list(begin);
	begin = tmp;
	// fprintf(stderr, "HELLO\n\n\n");
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_CMD)
		{
			cmd = ft_join_dstr(cmd, begin->str);
			if (!cmd)
			{
				ft_free_list(&data->exec);
				ft_pb_malloc(data);
				return (MAL_ERCODE); //GERER
			}
			cmd_quotes = ft_join_dstr(cmd_quotes, begin->quotes);
			if (!cmd_quotes)
			{
				ft_free_list(&data->exec);
				ft_pb_malloc(data);
				return (MAL_ERCODE); //GERER
			}
		}
		begin = begin->next;
	}
	begin = tmp;
	if (!ft_test_builtin(cmd))
		return (ft_free_dchar(cmd), ft_free_dchar(cmd_quotes), 0);
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_FALSEI)
		{
			tmp_fd = open(begin->str, O_RDWR);
			if (tmp_fd == -1)
			{
				perror(begin->str);
				err_value = 1;
				return(errno);
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
				return(errno);
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
				return(errno);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_APPEND)
		{
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (data->pip.fd_out == -1)
			{
				perror(begin->str);
				err_value = 1;
				return(errno);
			}
		}
		else if (begin->id == F_TRONC)
		{
			data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (data->pip.fd_out == -1)
			{
				perror(begin->str);
				err_value = 1;
				return(errno);
			}
		}
		else if (begin->id == F_INFILE)
		{
			data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
			if (data->pip.fd_in == -1)
			{
				perror(begin->str);
				err_value = 1;
				return(errno);
			}
		}
		begin = begin->next;
		
	}
	if (ft_exec_cmd_solo(data, cmd, cmd_quotes) == 1)
	{
		ft_free_dchar(cmd);
		ft_free_dchar(cmd_quotes);
		ft_free_list(&data->exec);
		return (1);
	}
	ft_free_dchar(cmd_quotes);
	ft_free_dchar(cmd);
	return (0);
}