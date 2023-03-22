/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:14:54 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 22:07:33 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_free_err_mal_cmd_solo(char **cmd, char **cmd_quotes, t_data *data)
{
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	ft_free_list(&data->exec);
	fprintf(stderr, "ERROR 0\n");
	ft_pb_malloc(data);
}

int	ft_exec_cmd_solo(t_data *data, char **cmd, char **cmd_quotes)
{
	if (!contain_token(&data->exec, F_CMD, 0))
		return (0);
	ft_dup_manage(data, 0);
	if (ft_test_builtin(cmd) == 1)
	{
		ft_close_all(data->pip, data);
		ft_exec_builtin(cmd, data, cmd_quotes);
		ft_init_in_out(data);
		dup2(data->pip.saved_stdin, 0);
		dup2(data->pip.saved_stdout, 1);
		return (1);
	}
	else
		return (0);
}

void	ft_free_child_exec_solo(t_data *data, char **cmd, char **cmd_quotes)
{
	(void) data;
	ft_free_dchar(cmd_quotes);
	ft_free_dchar(cmd);
}

int	ft_exec_built_in_solo_test_built_in(t_exec *begin, t_data *data, int *rt_val)
{
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_CMD)
		{
			data->to_free.cmd = ft_join_dstr(data->to_free.cmd, begin->str);
			if (!data->to_free.cmd)
			{
				ft_free_list(&data->exec);
				ft_pb_malloc(data);
			}
			data->to_free.cmd_quotes = ft_join_dstr(data->to_free.cmd_quotes, begin->quotes);
			if (!data->to_free.cmd_quotes)
			{
				ft_free_list(&data->exec);
				ft_pb_malloc(data);
			}
		}
		begin = begin->next;
	}
	if (!ft_test_builtin(data->to_free.cmd))
		return (ft_close_all(data->pip, data), ft_free_dchar(data->to_free.cmd), \
			ft_free_dchar(data->to_free.cmd_quotes), *rt_val = 0);
	return (*rt_val = 1);
}


int ft_ebs_falsin(t_exec *begin, t_data *data)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_RDWR);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, data->to_free.cmd_quotes);
		return (1);
	}
	ft_close(&tmp_fd);
	return (0);
}

int ft_ebs_fasea(t_exec *begin, t_data *data)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, data->to_free.cmd_quotes);
		return (1);
	}
	ft_close(&tmp_fd);
	return (0);
}
int ft_ebs_faset(t_exec *begin, t_data *data)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, data->to_free.cmd_quotes);
		return (1);
	}
	ft_close(&tmp_fd);
	return (0);
}
int ft_ebs_append(t_exec *begin, t_data *data)
{
	ft_close(&data->pip.fd_out);
	data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_APPEND, \
		0644);
	if (data->pip.fd_out == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, data->to_free.cmd_quotes);
		return (1);
	}
	return (0);
}
int ft_ebs_tronc(t_exec *begin, t_data *data)
{
	ft_close(&data->pip.fd_out);
	data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, \
		0644);
	if (data->pip.fd_out == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, data->to_free.cmd_quotes);
		return (1);
	}
	return (0);
}
int ft_ebs_infile(t_exec *begin, t_data *data)
{
	ft_close(&data->pip.fd_in);
	data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
	if (data->pip.fd_in == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, data->to_free.cmd_quotes);
		return (1);
	}
	return (0);
}

int	ft_exec_built_in_solo(t_exec *begin, t_data *data)
{
	t_exec	*tmp;
	int		rt_val;

	data->to_free.cmd = NULL;
	data->to_free.cmd_quotes = NULL;
	tmp = begin;
	if (ft_exec_built_in_solo_test_built_in(begin, data, &rt_val) != 1)
		return (rt_val);
	begin = tmp;
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_FALSEI && ft_ebs_falsin(begin, data) == 1)
			return (1);
		else if (begin->id == F_FALSEA && ft_ebs_fasea(begin, data) == 1)
			return (1);
		else if (begin->id == F_FALSET && ft_ebs_faset(begin, data) == 1)
			return (1);
		else if (begin->id == F_APPEND && ft_ebs_append(begin, data) == 1)
			return (1);
		else if (begin->id == F_TRONC && ft_ebs_tronc(begin, data) == 1)
			return (1);
		else if (begin->id == F_INFILE && ft_ebs_infile(begin, data) == 1)
			return (1);
		begin = begin->next;
	}
	if (ft_exec_cmd_solo(data, data->to_free.cmd, data->to_free.cmd_quotes) == 1)
	{
		ft_free_dchar(data->to_free.cmd);
		ft_free_dchar(data->to_free.cmd_quotes);
		return (1);
	}
	ft_free_dchar(data->to_free.cmd_quotes);
	ft_free_dchar(data->to_free.cmd);
	ft_close_all(data->pip, data);
	return (0);
}
