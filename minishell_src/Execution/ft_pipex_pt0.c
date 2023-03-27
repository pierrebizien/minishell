/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 19:19:16 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

char	**ft_get_paths(t_data *data, char **cmd, char **cmd_quotes)
{
	t_env	*tmp;
	char	**tab;

	tmp = &data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", ft_strlen(tmp->key)) == 0)
		{
			tab = ft_split(tmp->value, ':');
			if (tab == NULL)
				return (ft_free_dchar(cmd_quotes), ft_free_dchar(cmd), \
ft_free_dchar(data->to_free.env_tab), ft_free_list(&data->exec), \
ft_pb_malloc(data), NULL);
			return (tab);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_free_in_find_path(char **cmd, char **paths_env, \
	t_data *data, char **cmd_quotes)
{
	ft_close(&data->pip.saved_stdin);
	ft_close(&data->pip.saved_stdout);
	ft_free_dchar(data->to_free.env_tab);
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	ft_free_dchar(paths_env);
	ft_free_env(data);
	free(data->oldpwd);
	free(data->pwd);
	ft_close_all(data->pip, data);
	ft_free_list(&data->exec);
}

int	is_out(char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!str || !str[0])
		return (0);
	tmp = ft_split(str, '/');
	if (!tmp)
		return (-1);
	if (ft_strncmp(tmp[0], "dev", ft_strlen(tmp[0])) == 0 && \
		ft_strncmp(tmp[1], "stdout", ft_strlen(tmp[1])) == 0)
		return (ft_free_dchar(tmp), 1);
	ft_free_dchar(tmp);
	return (0);
}

int	contain_token(t_exec *begin, int token, int m)
{
	int		count;
	t_exec	*tmp;

	tmp = begin;
	begin = tmp;
	count = 0;
	while (begin && count < m)
	{
		if (begin->id == F_PIPE)
			count++;
		begin = begin->next;
	}
	while (begin && begin->id != F_PIPE)
	{
		if (begin->id == token && !is_out(begin->str))
			return (1);
		begin = begin->next;
	}
	begin = tmp;
	return (0);
}

void	ft_print_fd(t_data *data)
{
	fprintf(stderr, "fd in %d\n", data->pip.fd_in);
	fprintf(stderr, "fd out %d\n", data->pip.fd_out);
	fprintf(stderr, "pipefd1 [0] %d\n", data->pip.pipefd1[0]);
	fprintf(stderr, "pipefd1 [1] %d\n", data->pip.pipefd1[1]);
	fprintf(stderr, "pipefd2 [0]  %d\n", data->pip.pipefd2[0]);
	fprintf(stderr, "pipefd2 [1] %d\n", data->pip.pipefd2[1]);
}
