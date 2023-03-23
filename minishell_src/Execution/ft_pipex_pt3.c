/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 13:01:35 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

void	ft_exec_cmd(t_data *data, char **cmd, int m, char **cmd_quotes)
{
	if (!contain_token(&data->exec, F_CMD, m))
		return (ft_close_all(data->pip, data), ft_free_dchar(cmd_quotes), \
ft_free_dchar(cmd), ft_free_env(data), free(data->oldpwd), free(data->pwd), \
ft_free_list(&data->exec), exit(0));
	data->to_free.env_tab = ft_get_env(&data->env);
	if (data->to_free.env_tab == NULL)
		return (ft_free_dchar(cmd_quotes), ft_free_dchar(cmd), \
ft_free_list(&data->exec), fprintf(stderr, "error 21\n"), ft_pb_malloc(data));
	data->to_free.paths_env = ft_get_paths(data, cmd, cmd_quotes);
	data->to_free.path_exec = \
		find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
	ft_dup_manage(data, m);
	if (ft_exec_builtin(cmd, data, cmd_quotes) == 1)
	{
		free(data->to_free.path_exec);
		ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
		ft_close_all(data->pip, data);
		exit(g_err_value);
	}
	execve(data->to_free.path_exec, cmd, data->to_free.env_tab);
	free(data->to_free.path_exec);
	if (errno == 13)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
	perror("");
	exit(errno);
}

int	ft_child_exec(t_exec *begin, t_data *data, int m)
{
	int		tmp_fd;
	char	**cmd;
	char	**cmd_quotes;

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
				g_err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSEA)
		{
			tmp_fd = open(begin->str, M_C_RW | O_APPEND, 0644);
			if (tmp_fd == -1)
			{
				perror(begin->str);
				g_err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
			ft_close(&tmp_fd);
		}
		else if (begin->id == F_FALSET)
		{
			tmp_fd = open(begin->str, M_C_RW | O_TRUNC, 0644);
			if (tmp_fd == -1)
			{
				perror(begin->str);
				g_err_value = 1;
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
				ft_pb_malloc(data);
				return (MAL_ERCODE);
			}
			cmd_quotes = ft_join_dstr(cmd_quotes, begin->quotes);
			if (!cmd_quotes)
			{
				ft_free_list(&data->exec);
				ft_pb_malloc(data);
				return (MAL_ERCODE);
			}
		}
		else if (begin->id == F_APPEND)
		{
			ft_close(&data->pip.fd_out);
			data->pip.fd_out = open(begin->str, M_C_RW | O_APPEND, 0644);
			if (data->pip.fd_out == -1)
			{
				perror(begin->str);
				g_err_value = 1;
				ft_free_child_exec(data, cmd, cmd_quotes);
				exit(1);
			}
		}
		else if (begin->id == F_TRONC)
		{
			ft_close(&data->pip.fd_out);
			data->pip.fd_out = open(begin->str, M_C_RW | O_TRUNC, 0644);
			if (data->pip.fd_out == -1)
			{
				perror(begin->str);
				g_err_value = 1;
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
				g_err_value = 1;
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

void	ft_pipex(t_data *data)
{
	t_exec	*begin;
	int		m;

	begin = &data->exec;
	m = 0;
	if (!data->pip.nb_pipes)
		if (ft_exec_built_in_solo(begin, data))
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
	waitpid(data->pip.last_id, &g_err_value, 0);
	if (WIFEXITED(g_err_value))
		g_err_value = WEXITSTATUS(g_err_value);
	while (wait(NULL) != -1)
		(void)begin;
	ft_close_all(data->pip, data);
}
