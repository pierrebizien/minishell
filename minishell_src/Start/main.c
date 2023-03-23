/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:35:10 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 10:38:39 by ngriveau         ###   ########.fr       */
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

int	main(int ac, char **av, char**envp)
{
	char	*str;
	t_data	data;
	char	*cpy_str_tty;

	(void)ac;
	(void)av;
	ft_init(envp, &data);
	if (isatty(0) == 0)
		data.bool_redir_0 = 1;
	if (isatty(2) == 0)
		data.bool_redir_2 = 1;
	ft_init_sigint();
	ft_init_sigquit();
	if (!data.bool_redir_0 && !data.bool_redir_2)
		str = ft_prompt();
	else
	{
		str = get_next_line(0);
		if (str && ft_strlen(str) >= 1 && str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
	}
	add_history(str);
	cpy_str_tty = ft_strdup(str);
	while (str)
	{
		if (str && str[0])
		{
			str = ft_parse(str, &data);
			data.to_free.str = str;
			if (!str && g_err_value != -42 && (data.bool_redir_0 || \
				data.bool_redir_2))
				return (ft_putstr_fd(cpy_str_tty, 2), free(cpy_str_tty), \
					ft_close_all(data.pip, &data), g_err_value);
			free(cpy_str_tty);
			cpy_str_tty = NULL;
			if (str && !ft_parse_for_exec(&data))
			{
				if (g_err_value == MAL_ERCODE)
					return (g_err_value);
				ft_pipex(&data);
				ft_close_all(data.pip, &data);
				ft_unlink_hd(&data.exec);
				ft_free_list(&data.exec);
			}
			ft_close_all(data.pip, &data);
			ft_init_sigint();
			ft_init_sigquit();
			str = NULL;
		}
		free(cpy_str_tty);
		free(str);
		if (!data.bool_redir_0 && !data.bool_redir_2)
			str = ft_prompt();
		else
		{
			str = get_next_line(0);
			if (str && ft_strlen(str) >= 1 && str[ft_strlen(str) - 1] == '\n')
				str[ft_strlen(str) - 1] = '\0';
		}
		cpy_str_tty = ft_strdup(str);
		add_history(str);
	}
	free(cpy_str_tty);
	free(str);
	ft_close(&data.pip.saved_stdin);
	ft_close(&data.pip.saved_stdout);
	ft_free_end(&data);
	if (!data.bool_redir_0 && !data.bool_redir_2)
		write(2, "\nexit\n", 6);
	return (g_err_value);
}
