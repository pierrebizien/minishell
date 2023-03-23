/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 12:54:11 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

int	ft_search_hd_name(t_exec *begin, int m)
{
	t_exec	*tmp;
	int		fd;

	tmp = begin;
	while (m)
	{
		if (tmp->id == F_PIPE)
			m--;
		tmp = tmp->next;
	}
	while (tmp && tmp->id != F_PIPE)
	{
		if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ)
		{
			fd = open(tmp->hd_filename, O_RDONLY);
			if (fd == -1)
				return (-1);
			return (fd);
		}
		tmp = tmp->next;
	}
	return (-2);
}

int	ft_len_list(t_env *begin)
{
	t_env	*tmp;
	int		count;

	tmp = begin;
	count = 0;
	while (begin)
	{
		count++;
		begin = begin->next;
	}
	begin = tmp;
	return (count);
}

void	ft_reset_param_pip(t_data *data)
{
	data->pip.fd_in = 0;
	data->pip.fd_out = 1;
	data->pip.hd_in = 0;
}

void	ft_free_child_exec(t_data *data, char **cmd, char **cmd_quotes)
{
	ft_free_dchar(cmd_quotes);
	ft_free_dchar(cmd);
	ft_free_env(data);
	free(data->oldpwd);
	free(data->pwd);
	ft_close_all(data->pip, data);
	ft_free_list(&data->exec);
}

void	ft_init_in_out(t_data *data)
{
	ft_close(&data->pip.fd_in);
	ft_close(&data->pip.fd_out);
	data->pip.fd_in = dup(data->pip.saved_stdin);
	data->pip.fd_out = dup(data->pip.saved_stdout);
}
