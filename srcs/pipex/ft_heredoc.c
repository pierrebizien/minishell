/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/21 15:09:22 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	ft_heredoc(t_data *data)
{
	char	*str;

	data->tmp_fd = open("tmp-file.txt", O_TRUNC | O_CREAT | O_RDWR, 00777);
	if (data->tmp_fd == -1)
		return (ft_close(&data->fd_out), ft_free_dchar(data->paths), 1);
	data->limiter = data->av[2];
	write(1, "here_doc>", 10);
	str = get_next_line(0);
	if (str && (ft_p_strncmp(data->limiter, str, ft_p_strlen(data->limiter)) || \
		ft_p_strlen(str) != ft_p_strlen(data->limiter) + 1))
		write(data->tmp_fd, str, ft_p_strlen(str));
	while (str && (ft_p_strncmp(data->limiter, str, ft_p_strlen(data->limiter)) || \
		ft_p_strlen(str) != ft_p_strlen(data->limiter) + 1))
	{
		free(str);
		write(1, "here_doc>", 10);
		str = get_next_line(0);
		if (str && (ft_p_strncmp(data->limiter, str, ft_p_strlen(data->limiter)) || \
			ft_p_strlen(str) != ft_p_strlen(data->limiter) + 1))
			write(data->tmp_fd, str, ft_p_strlen(str));
	}
	free(str);
	ft_close(&data->tmp_fd);
	data->tmp_fd = open("tmp-file.txt", O_RDWR);
	if (data->tmp_fd == -1)
		return (ft_close(&data->fd_out), ft_free_dchar(data->paths), 1);
	data->fd_in = data->tmp_fd;
	return (0);
}

void	ft_init_pipe(t_data *data)
{
	data->pipefd1[0] = -1;
	data->pipefd1[1] = -1;
	data->pipefd2[0] = -1;
	data->pipefd2[1] = -1;
}
