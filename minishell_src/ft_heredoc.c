/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/02 14:55:12 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	ft_close(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

int	ft_heredoc(t_data *data, char *delimiter, int w)
{
	char	*str;

	if (w)
	{
		data->pip.tmp_fd = open("tmp-file.txt", O_TRUNC | O_CREAT | O_RDWR, 00777);
		if (data->pip.tmp_fd == -1)
			return (1); // GERER
	}
	write(1, ">", 1);
	str = get_next_line(0);
	if (w && str && (ft_strncmp(delimiter, str, ft_strlen(delimiter)) || \
		ft_strlen(str) != ft_strlen(delimiter) + 1))
		write(data->pip.tmp_fd, str, ft_strlen(str));
	while (str && (ft_strncmp(delimiter, str, ft_strlen(delimiter)) || \
		ft_strlen(str) != ft_strlen(delimiter) + 1))
	{
		free(str);
		write(1, ">", 1);
		str = get_next_line(0);
		if (w && str && (ft_strncmp(delimiter, str, ft_strlen(delimiter)) || \
			ft_strlen(str) != ft_strlen(delimiter) + 1))
			write(data->pip.tmp_fd, str, ft_strlen(str));
	}
	free(str);
	if(w)
	{
		ft_close(&data->pip.tmp_fd);
		data->pip.tmp_fd = open("tmp-file.txt", O_RDWR);
		if (data->pip.tmp_fd == -1)
			return (1); //gerer
		data->pip.fd_in = data->pip.tmp_fd;
	}
	return (0);
}
// int	ft_heredoc(t_pipex *data, int w)
// {
// 	char	*str;

// 	if (w)
// 	{
// 		data->tmp_fd = open("tmp-file.txt", O_TRUNC | O_CREAT | O_RDWR, 00777);
// 		if (data->tmp_fd == -1)
// 			return (ft_close(&data->fd_out), ft_free_dchar(data->paths), 1);
// 	}
// 	data->limiter = data->av[2];
// 	write(1, ">", 1);
// 	str = get_next_line(0);
// 	if (w && str && (ft_p_strncmp(data->limiter, str, ft_p_strlen(data->limiter)) || \
// 		ft_p_strlen(str) != ft_p_strlen(data->limiter) + 1))
// 		write(data->tmp_fd, str, ft_p_strlen(str));
// 	while (str && (ft_p_strncmp(data->limiter, str, ft_p_strlen(data->limiter)) || \
// 		ft_p_strlen(str) != ft_p_strlen(data->limiter) + 1))
// 	{
// 		free(str);
// 		write(1, ">", 1);
// 		str = get_next_line(0);
// 		if (w && str && (ft_p_strncmp(data->limiter, str, ft_p_strlen(data->limiter)) || \
// 			ft_p_strlen(str) != ft_p_strlen(data->limiter) + 1))
// 			write(data->tmp_fd, str, ft_p_strlen(str));
// 	}
// 	free(str);
// 	ft_close(&data->tmp_fd);
// 	data->tmp_fd = open("tmp-file.txt", O_RDWR);
// 	if (data->tmp_fd == -1)
// 		return (ft_close(&data->fd_out), ft_free_dchar(data->paths), 1);
// 	data->fd_in = data->tmp_fd;
// 	return (0);
// }

void	ft_init_pipex_pipe(t_data *data)
{
	data->pip.pipefd1[0] = -1;
	data->pip.pipefd1[1] = -1;
	data->pip.pipefd2[0] = -1;
	data->pip.pipefd2[1] = -1;
}
