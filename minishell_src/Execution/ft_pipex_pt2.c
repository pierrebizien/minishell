/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 14:41:55 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

char	*find_path_init(char **cmd, char **paths_env, t_data *data, \
	char **cmd_quotes)
{
	if (cmd && cmd[0] && !cmd[0][0])
		return (ft_putstr_fd(": Command not found\n", 2), \
ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	if (ft_strncmp(cmd[0], ".", ft_strlen(cmd[0])) == 0 || \
ft_strncmp(cmd[0], "..", ft_strlen(cmd[0])) == 0)
		return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd(": Command not found\n", \
2), ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	return (NULL);
}

char	*find_path_end(char **cmd, char **paths_env, t_data *data, \
	char **cmd_quotes)
{
	ft_putstr_fd(cmd[0], 2);
	if (ft_strchr(cmd[0], '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Command not found\n", 2);
	return (ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), \
		NULL);
}

char	*find_path_abs(char **cmd, char **paths_env, t_data *data, \
	char **cmd_quotes)
{
	char	*tmp;

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
	return (NULL);
}

char	*find_path_loop(char **cmd, char **paths_env, t_data *data, \
	char **cmd_quotes)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
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
	return (NULL);
}

char	*find_path(char **cmd, char **paths_env, t_data *data, \
	char **cmd_quotes)
{
	char	*tmp;
	int		i;

	i = 0;
	find_path_init(cmd, paths_env, data, cmd_quotes);
	if (ft_test_builtin(cmd) == 1)
		return (NULL);
	if ((cmd[0][0] == '/' || cmd[0][0] == '.') && access(cmd[0], F_OK))
		return (ft_putstr_fd(cmd[0], 2), \
ft_putstr_fd(": No such file or directory\n", 2), \
ft_free_in_find_path(cmd, paths_env, data, cmd_quotes), exit(127), NULL);
	tmp = find_path_abs(cmd, paths_env, data, cmd_quotes);
	if (tmp != NULL)
		return (tmp);
	tmp = find_path_loop(cmd, paths_env, data, cmd_quotes);
	if (tmp != NULL)
		return (tmp);
	return (find_path_end(cmd, paths_env, data, cmd_quotes));
}
