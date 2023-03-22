/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in_pt2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:21:26 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 22:22:16 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_ebs_infile(t_exec *begin, t_data *data)
{
	ft_close(&data->pip.fd_in);
	data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
	if (data->pip.fd_in == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, \
			data->to_free.cmd_quotes);
		return (1);
	}
	return (0);
}

int	ft_exec_built_in_solo_finish(t_data *data)
{
	if (ft_exec_cmd_solo(data, data->to_free.cmd, \
		data->to_free.cmd_quotes) == 1)
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
