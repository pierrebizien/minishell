/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in_pt2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:21:26 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 21:36:27 by ngriveau         ###   ########.fr       */
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

int	ft_export(char **cmd, t_data *data, char **cmd_quotes)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	if (ft_verif_option_export(cmd, cmd_quotes))
		return (2);
	if (ft_strstrlen(cmd) == 1)
		return (ft_just_export(data));
	while (cmd[i])
	{
		if (ft_verif_str_export(cmd[i]) == 0)
		{
			ft_export_putstr(cmd[i]);
			error = 1;
		}
		else if (ft_verif_str_export(cmd[i]) == 1)
			ft_export_local(cmd[i], data);
		else if (ft_verif_str_export(cmd[i]) == 2)
			ft_ok_export(cmd[i], data, cmd_quotes);
		else if (ft_verif_str_export(cmd[i]) == 3)
			ft_plus_egal_export(cmd[i], data, cmd_quotes);
		i++;
	}
	return (error);
}
