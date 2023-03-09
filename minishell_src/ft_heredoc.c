/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:39:00 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/09 15:09:58 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	ft_close(int *fd)
{
	if (*fd == -1 || *fd == 1 || *fd == 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	ft_manage_write(char *str, char *delimiter, t_data *data)
{
	int	i;
	// char *var;
	// char *tmp;

	i = 0;
	(void)delimiter;
	fprintf(stderr, "DELIMITER %s\n", delimiter);
	str = ft_convert_variable(str, data);
	write(data->pip.tmp_fd, str, ft_strlen(str));
	write (data->pip.tmp_fd, "\n", 1);
}
int	ft_heredoc(t_data *data, char *delimiter, int w)
{
	char	*str;

	fprintf(stderr, "DELIMITER ENTREE VAUT %s\n", delimiter);
	if (w)
	{
		data->pip.tmp_fd = open("tmp-file.txt", O_TRUNC | O_CREAT | O_RDWR, 00777);
		if (data->pip.tmp_fd == -1)
			return (1); // GERER
	}
	write(1, ">", 1);
	str = readline("tirien>");
	if (w && str && (ft_strncmp(delimiter, str, ft_strlen(delimiter)) || \
		ft_strlen(str) != ft_strlen(delimiter) + 1))
		ft_manage_write(str, delimiter, data);
	while (str && (ft_strncmp(delimiter, str, ft_strlen(delimiter)) || \
		ft_strlen(str) != ft_strlen(delimiter) + 1))
	{
		free(str);
		write(1, ">", 1);
		str =readline("tirien>");
		if (w && str && (ft_strncmp(delimiter, str, ft_strlen(delimiter)) || \
			ft_strlen(str) != ft_strlen(delimiter) + 1))
			ft_manage_write(str, delimiter, data);
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

void	ft_init_pipex_pipe(t_data *data)
{
	data->pip.pipefd1[0] = -1;
	data->pip.pipefd1[1] = -1;
	data->pip.pipefd2[0] = -1;
	data->pip.pipefd2[1] = -1;
}
