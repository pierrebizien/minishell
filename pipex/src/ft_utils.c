/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:18:33 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/27 16:47:50 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

int	ft_init_pipex(char **av, t_pipex *data, char**envp, int ac)
{
	ft_p_memset(&data->last_pid, 0, sizeof(data->last_pid));
	data->ac = ac;
	data->envp = envp;
	data->av = av;
	data->fd_out = -1;
	data->param1 = NULL;
	data->paths = ft_get_paths(envp);
	data->paths = ft_put_bs(data->paths);
	data->hd = 0;
	if (ft_p_strncmp(av[1], "here_doc", 8) != 0)
	{
		data->fd_in = open(av[1], O_RDONLY, 00644);
		if (data->fd_in == -1)
			ft_no_dir(av[1]);
	}
	else
		data->hd = 1;
	ft_init_pipex_pipe(data);
	return (0);
}

void	ft_first_child(t_pipex *data, char **av, char **envp)
{
	if (data->fd_in == -1)
	{
		ft_free_dchar(data->paths);
		ft_close_all(data);
		exit (1);
	}
	data->param1 = ft_p_split(av[2 + data->hd], ' ');
	if (!data->param1[0])
	{
		ft_finish_f1(data, av);
		exit(1);
	}
	if (ft_find_g_path(data, data->param1, 1) == -1)
	{
		ft_finish_f1(data, av);
		exit(1);
	}
	dup2(data->fd_in, 0);
	ft_close(&data->pipefd1[0]);
	// fprintf(stderr, "ici ua 4 ou quoi \t\t%d\n", data->ac);
	if (data->ac  == 4)
	{
		if (data->hd == 0)
			data->fd_out = open(data->av[data->ac - 1], O_RDWR | O_TRUNC | O_CREAT, 00644);
		else
			data->fd_out = open(data->av[data->ac - 1], O_RDWR | O_APPEND | O_CREAT, 00644);
		dup2(data->fd_out, 1);
		ft_close(&data->pipefd1[1]);
		ft_exec(data);
		exit(1);
	}
	dup2(data->pipefd1[1], 1);
	ft_close(&data->pipefd1[1]);
	ft_exec(data);
	(void)envp;
}

void	ft_last_child_bis(t_pipex *data, char **envp, int i)
{
	if (i % 2 == 0)
	{
		ft_close(&data->pipefd1[1]);
		dup2(data->pipefd1[0], 0);
		ft_close(&data->pipefd1[0]);
	}
	else
	{
		ft_close(&data->pipefd2[1]);
		dup2(data->pipefd2[0], 0);
		ft_close(&data->pipefd2[0]);
	}
	dup2(data->fd_out, 1);
	ft_close(&data->fd_out);
	ft_exec(data);
	(void)envp;
}

void	ft_last_child(t_pipex *data, char **av, char **envp, int i)
{
	if (data->hd == 0)
		data->fd_out = open(data->av[data->ac - 1], O_RDWR | O_TRUNC | O_CREAT, 00644);
	else
		data->fd_out = open(data->av[data->ac - 1], O_RDWR | O_APPEND | O_CREAT, 00644);	
	if (data->fd_out == -1)
	{
		perror(data->av[data->ac - 1]);
		ft_finish_lf_bis(data);
		exit (1);
	}
	data->param1 = ft_p_split(av[i + 3 + data->hd], ' ');
	if (data->param1[0] == NULL)
	{
		ft_finish_lf(data, av, i);
		exit (1);
	}
	if (ft_find_g_path(data, data->param1, 1) == -1)
	{
		ft_finish_lf(data, av, i);
		exit (EXIT_FAILURE);
	}
	ft_last_child_bis(data, envp, i);
}

int	ft_main_suite(t_pipex *data, char **av, char **envp)
{
	int	id;
	int	i;

	pipe(data->pipefd1);
	id = fork();
	if (id == 0)
		ft_first_child(data, av, envp);
	else
	{
		if (data->ac == 4)
		{
			data->last_pid = id;
			return (ft_end(data)); //GERER VALIOU
		}
		i = ft_middle(data);
		data->last_pid = fork();
		if (data->last_pid == 0)
			ft_last_child(data, av, envp, i);
	}
	return (ft_end(data));
}
