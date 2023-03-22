/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_pt0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 23:29:41 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_heredoc_end(t_data *data, char *delimiter, int w, char *str)
{
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
}

char	*ft_heredoc_init_var(t_data *data, int w)
{
	data->to_free.w = w;
	data->to_free.hd_break = 0;
	return (NULL);
}

int	ft_heredoc_maxi_while(char **str, t_data *data, char *delimiter, int sq)
{
	free(*str);
	rl_event_hook = event;
	*str = ft_heredoc_prompt(*str, data);
	if (g_err_value == 130)
		data->to_free.hd_break = 1;
	if (!sq && *str)
	{
		*str = ft_convert_variable_hd(*str, data, delimiter);
		if (!*str)
			return (1);
	}
	if (data->to_free.w && *str && ft_strncmp(delimiter, *str, \
		ft_strlen(delimiter) + 1))
		ft_manage_write(*str, delimiter, data, sq);
	return (0);
}

char	*ft_heredoc(t_data *data, char *delimiter, int w, int sq)
{
	char	*str;
	char	*name;

	str = NULL;
	name = ft_heredoc_init_var(data, w);
	if (w && ft_heredoc_if_w(&name, data) == 0)
		return (NULL);
	str = ft_heredoc_prompt(str, data);
	if (g_err_value == 130)
		return (free(name), free(str), NULL);
	if (!sq && str)
	{
		str = ft_convert_variable_hd(str, data, delimiter);
		if (!str)
			return (NULL);
	}
	if (w && str && ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1))
		ft_manage_write(str, delimiter, data, sq);
	while (str && data->to_free.hd_break == 0 && (ft_strncmp(delimiter, \
		str, ft_strlen(delimiter) + 1)))
		if (ft_heredoc_maxi_while(&str, data, delimiter, sq) == 1)
			return (NULL);
	if (g_err_value == 130)
		return (free(name), free(str), NULL);
	return (ft_heredoc_end(data, delimiter, w, str), name);
}

void	ft_init_pipex_pipe(t_data *data)
{
	data->pip.pipefd1[0] = -1;
	data->pip.pipefd1[1] = -1;
	data->pip.pipefd2[0] = -1;
	data->pip.pipefd2[1] = -1;
}
