/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_pt1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 13:39:38 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_manage_write(char *str, char *delimiter, t_data *data, int sq)
{
	int	i;

	i = 0;
	(void)sq;
	(void)delimiter;
	write(data->pip.tmp_fd, str, ft_strlen(str));
	write (data->pip.tmp_fd, "\n", 1);
}

int	ft_heredoc_if_w(char **name, t_data *data)
{
	*name = ft_randomstr("/tmp/hd_", NULL, 16);
	if (*name == NULL)
	{
		g_err_value = MAL_ERCODE;
		return (0);
	}
	data->pip.tmp_fd = open(*name, O_TRUNC | O_CREAT | O_RDWR, 00777);
	if (data->pip.tmp_fd == -1)
		return (free(*name), 0);
	return (1);
}

char	*ft_heredoc_prompt(char *str, t_data *data)
{
	if (!data->bool_redir_0 && !data->bool_redir_2)
		str = readline(">");
	else
	{
		str = get_next_line(0);
		if (str && ft_strlen(str) >= 1 && str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
	}
	return (str);
}
