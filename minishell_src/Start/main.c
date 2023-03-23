/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:35:10 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 11:36:36 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	g_err_value;

char	*ft_prompt(void)
{
	char	*path;
	char	*minipath;
	char	*str;
	int		i;

	i = 0;
	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	while (path && path[i])
		i++;
	i--;
	while (path && path[i] != '/')
		i--;
	i++;
	minipath = ft_substr(path, i, ft_strlen(path + i));
	free(path);
	path = ft_put_str_in_str("\001\e[36;1m\002minishell \
(\001\e[32;1m\002/\001\e[36;1m\002) \001\e[0m\002", minipath, 30);
	free(minipath);
	str = readline(path);
	free(path);
	return (str);
}

char	*ft_input(t_data *data)
{
	char	*str;

	if (!data->bool_redir_0 && !data->bool_redir_2)
		str = ft_prompt();
	else
	{
		str = get_next_line(0);
		if (str && ft_strlen(str) >= 1 && str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
	}
	add_history(str);
	return (str);
}

int	main_pt2(t_data *data)
{
	data->to_free.str = ft_parse(data->to_free.str, data);
	if (!data->to_free.str && g_err_value != -42 && (data->bool_redir_0 || \
		data->bool_redir_2))
		return (ft_putstr_fd(data->to_free.cpy_str_tty, 2), \
			free(data->to_free.cpy_str_tty), ft_close_all(data->pip, data), \
			exit(g_err_value), -22);
	free(data->to_free.cpy_str_tty);
	data->to_free.cpy_str_tty = NULL;
	if (data->to_free.str && !ft_parse_for_exec(data))
	{
		if (g_err_value == MAL_ERCODE)
			exit(g_err_value);
		ft_pipex(data);
		ft_close_all(data->pip, data);
		ft_unlink_hd(&data->exec);
		ft_free_list(&data->exec);
	}
	ft_close_all(data->pip, data);
	ft_init_sigint();
	ft_init_sigquit();
	data->to_free.str = NULL;
	return (1);
}

int	main(int ac, char **av, char**envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	ft_init(envp, &data);
	data.to_free.str = ft_input(&data);
	data.to_free.cpy_str_tty = ft_strdup(data.to_free.str);
	while (data.to_free.str)
	{
		if (data.to_free.str && data.to_free.str[0])
			main_pt2(&data);
		free(data.to_free.cpy_str_tty);
		free(data.to_free.str);
		data.to_free.str = ft_input(&data);
		data.to_free.cpy_str_tty = ft_strdup(data.to_free.str);
	}
	if (!data.bool_redir_0 && !data.bool_redir_2)
		write(2, "\nexit\n", 6);
	return (free(data.to_free.cpy_str_tty), free(data.to_free.str), \
		ft_close(&data.pip.saved_stdin), ft_close(&data.pip.saved_stdout), \
		ft_free_end(&data), g_err_value);
}
