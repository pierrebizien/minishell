/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/13 14:59:27 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

extern int err_value;

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
	// char *var;
	// char *tmp;

	i = 0;
	(void)sq;
	(void)delimiter;

	write(data->pip.tmp_fd, str, ft_strlen(str));
	write (data->pip.tmp_fd, "\n", 1);
}
char	*ft_heredoc(t_data *data, char *delimiter, int w, int sq)
{
	char	*str;
	char	*name;

	if (w)
	{
		name = ft_randomstr("/tmp/hd_", NULL, 16);
		data->pip.tmp_fd = open(name, O_TRUNC | O_CREAT | O_RDWR, 00777);
		if (data->pip.tmp_fd == -1)
			return (NULL); // GERER
	}
	str = readline(">");
	if (err_value == 130)
	{
		//FREE TOUT LE TINTOUIN
		//MEME TINTOUIN QU EN DESSOUS METTRE DANS FONCTION PUR LA NONO
		data->last_err_num = 130;
		return (NULL);
	}
	if (!sq)
		str = ft_convert_variable_hd(str, data, delimiter);
	if (w && str && ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1))
		ft_manage_write(str, delimiter, data, sq);
	while (str && (ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1)))
	{
		free(str);

		rl_event_hook=event;
		str = readline(">");
		if (err_value == 130)
			break;
		if (!sq)
			str = ft_convert_variable_hd(str, data, delimiter);
		if (w && str && ft_strncmp(delimiter, str, ft_strlen(delimiter) + 1))
			ft_manage_write(str, delimiter, data, sq);
	}
	if (err_value == 130)
	{
		//FREE TOUT LE TINTOUIN
		data->last_err_num = 130;
		return (NULL);
	}
	free(str);
	if(w)
	{
		ft_close(&data->pip.tmp_fd);
		// data->pip.tmp_fd = open(name, O_RDWR);
		// if (data->pip.tmp_fd == -1)
		// 	return (NULL); //gerer
		// data->pip.fd_in = data->pip.tmp_fd;
	}
	return (name); 
}

void	ft_init_pipex_pipe(t_data *data)
{
	data->pip.pipefd1[0] = -1;
	data->pip.pipefd1[1] = -1;
	data->pip.pipefd2[0] = -1;
	data->pip.pipefd2[1] = -1;
}
