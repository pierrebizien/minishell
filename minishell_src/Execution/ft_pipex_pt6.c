/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_pt6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:43:04 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 18:15:30 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_err_value;

int	ft_child_exec(t_exec *begin, t_data *data, int m)
{
	char	**cmd;
	char	**cmd_quotes;

	ft_init_sigint_exec();
	ft_init_sigquit_exec();
	cmd = NULL;
	cmd_quotes = NULL;
	ft_c_e_while(begin, data, &cmd, &cmd_quotes);
	ft_exec_cmd(data, cmd, m, cmd_quotes);
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	return (0);
}

void	ft_pipex_pt2(t_data *data, t_exec **begin, int *m)
{
	ft_init_in_out(data);
	if (!*m || *m % 2 == 0)
		pipe(data->pip.pipefd1);
	else
		pipe(data->pip.pipefd2);
	signal(SIGINT, SIG_IGN);
	data->pip.last_id = fork();
	if (data->pip.last_id == 0)
		ft_child_exec(*begin, data, *m);
	if (!*m || *m % 2 == 0)
	{
		ft_close(&data->pip.pipefd2[0]);
		ft_close(&data->pip.pipefd1[1]);
	}
	else
	{
		ft_close(&data->pip.pipefd1[0]);
		ft_close(&data->pip.pipefd2[1]);
	}
	while (*begin && (*begin)->id != F_PIPE)
		*begin = (*begin)->next;
	if (*begin && (*begin)->id == F_PIPE)
		*begin = (*begin)->next;
	*m = *m + 1;
}

void	ft_pipex(t_data *data)
{
	t_exec	*begin;
	int		m;

	begin = &data->exec;
	m = 0;
	if (!data->pip.nb_pipes)
		if (ft_exec_built_in_solo(begin, data))
			return ;
	begin = &data->exec;
	while (begin)
		ft_pipex_pt2(data, &begin, &m);
	waitpid(data->pip.last_id, &g_err_value, 0);
	if (WIFEXITED(g_err_value))
		g_err_value = WEXITSTATUS(g_err_value);
	if (g_err_value == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	while (wait(NULL) != -1)
		(void)begin;
	ft_close_all(data->pip, data);
}
