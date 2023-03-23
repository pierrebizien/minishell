/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 13:39:07 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

void	ft_dup_manage_bis(t_data *data, int m)
{
	if (contain_token(&data->exec, F_APPEND, m) || \
		contain_token(&data->exec, F_TRONC, m) || m == data->pip.nb_pipes)
	{
		dup2(data->pip.fd_out, 1);
	}
	else if (!m || m % 2 == 0)
	{
		ft_close(&data->pip.pipefd1[0]);
		dup2(data->pip.pipefd1[1], 1);
		ft_close(&data->pip.pipefd1[1]);
	}
	else
	{
		ft_close(&data->pip.pipefd2[0]);
		dup2(data->pip.pipefd2[1], 1);
		ft_close(&data->pip.pipefd2[1]);
	}
}

void	ft_dup_manage(t_data *data, int m)
{
	int	tmp_fd;

	if (contain_token(&data->exec, F_DELIMITER, m) || \
		contain_token(&data->exec, F_DELIMITER_SQ, m))
	{
		tmp_fd = ft_search_hd_name(&data->exec, m);
		dup2(tmp_fd, 0);
		ft_close(&tmp_fd);
	}
	else if (!m || contain_token(&data->exec, F_INFILE, m))
		dup2(data->pip.fd_in, 0);
	else if (m && m % 2 == 0)
	{
		ft_close(&data->pip.pipefd2[1]);
		dup2(data->pip.pipefd2[0], 0);
		ft_close(&data->pip.pipefd2[0]);
	}
	else
	{
		ft_close(&data->pip.pipefd1[1]);
		dup2(data->pip.pipefd1[0], 0);
		ft_close(&data->pip.pipefd1[0]);
	}
	ft_dup_manage_bis(data, m);
}

char	**ft_get_env(t_env *env)
{
	t_env	*tmp;
	char	**output;
	int		k;

	tmp = env;
	k = 0;
	output = malloc(sizeof(char *) * (ft_len_list(env) + 1));
	if (!output)
		return (NULL);
	output[ft_len_list(env)] = 0;
	while (env)
	{
		output[k] = malloc(sizeof(char) * (ft_strlen(env->key) + \
			ft_strlen(env->value) + 2));
		if (!output[k])
			return (ft_free_dchar(output), NULL);
		ft_memcpy(output[k], env->key, ft_strlen(env->key));
		output[k][ft_strlen(env->key)] = '=';
		ft_memcpy(output[k] + ft_strlen(env->key) + 1, env->value, \
			ft_strlen(env->value) + 1);
		k++;
		env = env->next;
	}
	env = tmp;
	return (output);
}
