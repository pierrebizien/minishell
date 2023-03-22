/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 22:34:57 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_close(int *fd)
{
	if (*fd == -1 || *fd == 1 || *fd == 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	ft_manage_write(char *str, char *delimiter, t_data *data, int sq)
{
	int	i;

	i = 0;
	(void)sq;
	(void)delimiter;
	write(data->pip.tmp_fd, str, ft_strlen(str));
	write (data->pip.tmp_fd, "\n", 1);
}


int ft_heredoc_if_w(char *name, t_data *data) 
{
	name = ft_randomstr("/tmp/hd_", NULL, 16);
	if (name == NULL)
	{
		g_err_value = MAL_ERCODE;
		return (0);
	}
	data->pip.tmp_fd = open(name, O_TRUNC | O_CREAT | O_RDWR, 00777);
	if (data->pip.tmp_fd == -1)
		return (free(name), 0);
	return (1);
}

char	*ft_heredoc(t_data *data, char *delimiter, int w, int sq)
{
	char	*str;
	char	*name;

	if (w && ft_heredoc_if_w(name, data) == 0)
		return (NULL);
	if (!data->bool_redir_0 && !data->bool_redir_2)
		str = readline(">");
	else
	{
		str = get_next_line(0);
		if (str && ft_strlen(str) >= 1 && str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
	}
	if (g_err_value == 130)
	{
		free(name);
		free(str);
		return (NULL);
	}
	if (!sq && str)
	{
		str = ft_convert_variable_hd(str, data, delimiter);
		if (!str)
			return (NULL);
	}
	if (w && str && ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1))
		ft_manage_write(str, delimiter, data, sq);
	while (str && (ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1)))
	{
		free(str);
		rl_event_hook = event;
		if (!data->bool_redir_0 && !data->bool_redir_2)
			str = readline(">");
		else
		{
			str = get_next_line(0);
			if (ft_strlen(str) > 0 && str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = '\0';
		}
		if (g_err_value == 130)
			break ;
		if (!sq && str)
		{
			str = ft_convert_variable_hd(str, data, delimiter);
			if (!str)
				return (NULL);
		}
		if (w && str && ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1))
			ft_manage_write(str, delimiter, data, sq);
	}
	if (g_err_value == 130)
	{
		free(name);
		free(str);
		return (NULL);
	}
	if (!str)
	{
		ft_putstr_fd(\
"warning: here-document delimited by end-of-file (wanted '", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (w)
		ft_close(&data->pip.tmp_fd);
	free(str);
	return (name);
}

void	ft_init_pipex_pipe(t_data *data)
{
	data->pip.pipefd1[0] = -1;
	data->pip.pipefd1[1] = -1;
	data->pip.pipefd2[0] = -1;
	data->pip.pipefd2[1] = -1;
}
