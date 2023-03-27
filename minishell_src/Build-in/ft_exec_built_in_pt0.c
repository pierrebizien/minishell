/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in_pt0.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:14:54 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 18:12:31 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_free_err_mal_cmd_solo(char **cmd, char **cmd_quotes, t_data *data)
{
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	ft_free_list(&data->exec);
	ft_pb_malloc(data);
}

int	ft_exec_cmd_solo(t_data *data, char **cmd, char **cmd_quotes)
{
	if (!contain_token(&data->exec, F_CMD, 0))
		return (0);
	// write(1, "TEST\n\n\n", 7);
	ft_dup_manage(data, 0);
	if (ft_test_builtin(cmd) == 1)
	{
		ft_exec_builtin(cmd, data, cmd_quotes);
		ft_init_in_out(data);
		dup2(data->pip.saved_stdin, 0);
		dup2(data->pip.saved_stdout, 1);
		ft_close_all(data->pip, data);
		// fprintf(stderr, "data->pip.saved_stdin = %d\n", data->pip.saved_stdout);
		// fprintf(stderr, "data->pip.saved_stdin = %d\n", data->pip.saved_stdout);
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

int	ft_exec_built_in_solo_test_builtin(t_exec *begin, t_data *data, int *rt_val)
{
	data->to_free.cmd = NULL;
	data->to_free.cmd_quotes = NULL;
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_CMD)
		{
			data->to_free.cmd = ft_join_dstr(data->to_free.cmd, begin->str);
			if (!data->to_free.cmd)
				return (ft_free_list(&data->exec), ft_pb_malloc(data), -22);
			data->to_free.cmd_quotes = ft_join_dstr(data->to_free.cmd_quotes, \
				begin->quotes);
			if (!data->to_free.cmd_quotes)
				return (ft_free_dchar(data->to_free.cmd), \
					ft_free_list(&data->exec), ft_pb_malloc(data), -22);
		}
		begin = begin->next;
	}
	if (!ft_test_builtin(data->to_free.cmd))
		return (ft_close_all(data->pip, data), ft_free_dchar(data->to_free.cmd) \
			, ft_free_dchar(data->to_free.cmd_quotes), *rt_val = 0);
	return (*rt_val = 1);
}

int	ft_exec_built_in_solo(t_exec *begin, t_data *data)
{
	t_exec	*tmp;
	int		rt_val;

	tmp = begin;
	if (ft_exec_built_in_solo_test_builtin(begin, data, &rt_val) != 1)
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
	return (ft_exec_built_in_solo_finish(data));
}
