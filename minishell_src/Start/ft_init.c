/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:28:58 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 11:53:15 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	event(void)
{
	return (42);
}

void	ft_init_data(char **env, t_data *data)
{
	data->sep = "|";
	data->envp = env;
	data->hd = 0;
	data->pwd = getcwd(NULL, 0);
	data->oldpwd = getcwd(NULL, 0);
	data->pip.fd_in = 0;
	data->pip.last_id = -1;
	data->last_err_num = 0;
	data->err_built_in = 1;
	data->bool_redir_0 = 0;
	data->bool_redir_2 = 0;
	data->pip.saved_stdin = dup(0);
	data->pip.saved_stdout = dup(1);
	data->pip.fd_out = 1;
	data->pip.hd_in = 0;
	data->to_free.env_tab = NULL;
	data->to_free.path_exec = NULL;
	data->to_free.paths_env = NULL;
	data->to_free.str = NULL;
	data->to_free.cmd = NULL;
	data->to_free.cmd_quotes = NULL;
	data->just_export = NULL;
}

int	ft_init(char **env, t_data *data)
{
	ft_logo();
	ft_init_data(env, data);
	ft_init_pipex_pipe(data);
	ft_create_env(env, data);
	rl_event_hook = event;
	rl_outstream = stderr;
	if (isatty(0) == 0)
		data->bool_redir_0 = 1;
	if (isatty(2) == 0)
		data->bool_redir_2 = 1;
	ft_init_sigint();
	ft_init_sigquit();
	return (0);
}
