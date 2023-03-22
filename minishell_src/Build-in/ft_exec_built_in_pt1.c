/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built_in_pt1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:21:26 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 22:22:21 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_ebs_falsin(t_exec *begin, t_data *data)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_RDWR);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, \
			data->to_free.cmd_quotes);
		return (1);
	}
	ft_close(&tmp_fd);
	return (0);
}

int	ft_ebs_fasea(t_exec *begin, t_data *data)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, \
			data->to_free.cmd_quotes);
		return (1);
	}
	ft_close(&tmp_fd);
	return (0);
}

int	ft_ebs_faset(t_exec *begin, t_data *data)
{
	int		tmp_fd;

	tmp_fd = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, \
			data->to_free.cmd_quotes);
		return (1);
	}
	ft_close(&tmp_fd);
	return (0);
}

int	ft_ebs_append(t_exec *begin, t_data *data)
{
	ft_close(&data->pip.fd_out);
	data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_APPEND, \
		0644);
	if (data->pip.fd_out == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, \
			data->to_free.cmd_quotes);
		return (1);
	}
	return (0);
}

int	ft_ebs_tronc(t_exec *begin, t_data *data)
{
	ft_close(&data->pip.fd_out);
	data->pip.fd_out = open(begin->str, O_CREAT | O_RDWR | O_TRUNC, \
		0644);
	if (data->pip.fd_out == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec_solo(data, data->to_free.cmd, \
			data->to_free.cmd_quotes);
		return (1);
	}
	return (0);
}
