/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 14:42:14 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

void	ft_c_e_cmd(t_exec *begin, t_data *data, char ***cmd, char ***quotes)
{
	*cmd = ft_join_dstr(*cmd, begin->str);
	if (!*cmd)
	{
		ft_free_list(&data->exec);
		ft_pb_malloc(data);
		return ;
	}
	*quotes = ft_join_dstr(*quotes, begin->quotes);
	if (!*quotes)
	{
		ft_free_list(&data->exec);
		ft_pb_malloc(data);
		return ;
	}
}

void	ft_c_e_append(t_exec *begin, t_data *data, char **cmd, char **quotes)
{
	ft_close(&data->pip.fd_out);
	data->pip.fd_out = open(begin->str, M_C_RW | O_APPEND, 0644);
	if (data->pip.fd_out == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec(data, cmd, quotes);
		exit(1);
	}
}

void	ft_c_e_tronc(t_exec *begin, t_data *data, char **cmd, char **quotes)
{
	ft_close(&data->pip.fd_out);
	data->pip.fd_out = open(begin->str, M_C_RW | O_TRUNC, 0644);
	if (data->pip.fd_out == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec(data, cmd, quotes);
		exit(1);
	}
}

void	ft_c_e_infile(t_exec *begin, t_data *data, char **cmd, char **quotes)
{
	ft_close(&data->pip.fd_in);
	data->pip.fd_in = open(begin->str, O_RDONLY, 0644);
	if (data->pip.fd_in == -1)
	{
		perror(begin->str);
		g_err_value = 1;
		ft_free_child_exec(data, cmd, quotes);
		exit(1);
	}
}

void	ft_c_e_while(t_exec *begin, t_data *data, char ***cmd, char ***quotes)
{
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == F_FALSEI)
			ft_c_e_falsei(begin, data, *cmd, *quotes);
		else if (begin->id == F_FALSEA)
			ft_c_e_falsea(begin, data, *cmd, *quotes);
		else if (begin->id == F_FALSET)
			ft_c_e_falset(begin, data, *cmd, *quotes);
		else if (begin->id == F_CMD)
			ft_c_e_cmd(begin, data, cmd, quotes);
		else if (begin->id == F_APPEND)
			ft_c_e_append(begin, data, *cmd, *quotes);
		else if (begin->id == F_TRONC)
			ft_c_e_tronc(begin, data, *cmd, *quotes);
		else if (begin->id == F_INFILE)
			ft_c_e_infile(begin, data, *cmd, *quotes);
		begin = begin->next;
	}	
}
