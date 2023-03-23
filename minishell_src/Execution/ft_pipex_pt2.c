/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 13:01:44 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

char	*find_path(char **cmd, char **paths_env, t_data *data, \
	char **cmd_quotes)
{
	char	*tmp;
	int		i;

	i = 0;
	if (cmd && cmd[0] && !cmd[0][0])
		return (ft_putstr_fd(": Command not found\n", 2), \
ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (ft_strncmp(cmd[0], ".", ft_strlen(cmd[0])) == 0 || \
ft_strncmp(cmd[0], "..", ft_strlen(cmd[0])) == 0)
		return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": Command not found\n", \
2), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (ft_test_builtin(cmd) == 1)
		return (NULL);
	if ((cmd[0][0] == '/' || cmd[0][0] == '.') && access(cmd[0], F_OK))
		return (ft_putstr_fd(cmd[0], 2), \
ft_putstr_fd(": No such file or directory\n", 2), \
ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (!access(cmd[0], F_OK))
	{
		if (access(cmd[0], X_OK))
			return (perror(cmd[0]), \
ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(126), NULL);
		else
		{
			tmp = ft_strdup(cmd[0]);
			if (tmp == NULL)
				return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), \
				ft_putstr_fd(MALLOC_ERROR, 2), exit(MAL_ERCODE), NULL);
			return (tmp);
		}
	}
	while (paths_env && paths_env[i])
	{
		tmp = ft_strrjoin(paths_env[i], "/", cmd[0]);
		if (!tmp)
			return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), \
				ft_putstr_fd(MALLOC_ERROR, 2), exit(MAL_ERCODE), NULL);
		if (!access(tmp, F_OK))
		{
			if (access(tmp, X_OK))
				return (perror(cmd[i]), free(tmp), ft_free_in_find_path(cmd, \
					paths_env, data, cmd_quotes), exit(126), NULL);
			else
				return (tmp);
		}
		i++;
		free(tmp);
	}
	ft_putstr_fd(cmd[0], 2);
	if (ft_strchr(cmd[0], '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Command not found\n", 2);
	return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), \
		NULL);
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
	{
		dup2(data->pip.fd_in, 0);
	}
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

char	**ft_get_env(t_env *env)
{
	t_env	*tmp;
	char	**output;
	int		k;
	int		count;

	count = 0;
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
		count++;
	}
	env = tmp;
	return (output);
}
