/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:42:16 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/07 17:53:03 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

void	ft_close_if(int *fd, t_pipex *data)
{
	if (data->hd == 0 && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	ft_exec(t_pipex *data)
{
	char	*str;

	ft_close_all(data);
	str = ft_p_strjoin(data->paths[data->npath1], data->param1[0]);
	// fprintf(stderr, "LAAAAA");
	// ft_print_dchar(data->param1);
	execve(str, data->param1, data->envp);
	perror(data->param1[0]);
	ft_free_dchar(data->param1);
	ft_free_dchar(data->paths);
	free(str);
	exit(1);
}

void	ft_exec_f(t_pipex *data)
{
	char	*str;

	ft_close_all(data);
	// fprintf(stderr, "LOOOOO\n\n");
	str = ft_p_strjoin(data->paths[data->npath1], data->param1[0]);
	// fprintf(stderr, "LOOOOO\n\n");
	// fprintf(stderr, "LAAAAA\n\n");
	ft_print_dchar(data->param1);
	execve(str, data->param1, data->envp);
	perror(data->param1[0]);
	ft_free_dchar(data->param1);
	ft_free_dchar(data->paths);
	free(str);
	exit(1);
}
