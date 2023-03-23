/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 15:00:41 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

void	ft_exec_cmd_is_a_dir(t_data *data, char **cmd, char **cmd_quotes)
{
	if (errno == 13)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
}

void	ft_exec_cmd(t_data *data, char **cmd, int m, char **cmd_quotes)
{
	if (!contain_token(&data->exec, F_CMD, m))
		return (ft_close_all(data->pip, data), ft_free_dchar(cmd_quotes), \
ft_free_dchar(cmd), ft_free_env(data), free(data->oldpwd), free(data->pwd), \
ft_free_list(&data->exec), exit(0));
	data->to_free.env_tab = ft_get_env(&data->env);
	if (data->to_free.env_tab == NULL)
		return (ft_free_dchar(cmd_quotes), ft_free_dchar(cmd), \
ft_free_list(&data->exec), ft_pb_malloc(data));
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
	ft_exec_cmd_is_a_dir(data, cmd, cmd_quotes);
	ft_free_in_find_path(cmd, data->to_free.paths_env, data, cmd_quotes);
	perror("");
	exit(errno);
}

void	ft_c_e_falsei(t_exec *begin, t_data *data, char **cmd, char **quotes)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_RDWR);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec(data, cmd, quotes);
		exit(1);
	}
	ft_close(&tmp_fd);
}

void	ft_c_e_falsea(t_exec *begin, t_data *data, char **cmd, char **quotes)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, M_C_RW | O_APPEND, 0644);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec(data, cmd, quotes);
		exit(1);
	}
	ft_close(&tmp_fd);
}

void	ft_c_e_falset(t_exec *begin, t_data *data, char **cmd, char **quotes)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, M_C_RW | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec(data, cmd, quotes);
		exit(1);
	}
	ft_close(&tmp_fd);
}
