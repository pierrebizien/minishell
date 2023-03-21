#include "../_Include/minishell.h"

int		err_value;

void	ft_print_dargs(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		printf("|%s| \n", strstr[i]);
		i++;
	}
	
}
// void	ft_print_dchar(char **strstr)
// {
// 	int	i;

// 	i = 0;
// 	while (strstr && strstr[i])
// 	{
// 		fprintf(stderr, "tab[%d] = |%s|\n", i, strstr[i]);
// 		i++;
// 	}
// 	if (!strstr)
// 		fprintf(stderr, "STRSTR N EXISTE PAS\n");
// }


char *ft_prompt(void)
{
	char *path;
	char *minipath;
	int i;

	i = 0;
	path = getcwd(NULL, 0);
	if (!path)
		return (NULL); //GERER
	while (path && path[i])
		i++;
	i--;
	while (path && path[i] != '/')
		i--;
	i++;
	minipath = ft_substr(path, i, ft_strlen(path + i));
	free(path);
	path = ft_put_str_in_str("\001\e[36;1m\002minishell (\001\e[32;1m\002/\001\e[36;1m\002) \001\e[0m\002", minipath, 30);
	// path = ft_put_str_in_str(path, ft_itoa(err_value), 0);
	// path = ft_put_str_in_str("\e[36;1mminishell (\e[32;1m/\e[36;1m) \e[0m", minipath, 26);
	//GLOBAL POUR 2
	char *str = readline(path);
	free(path);
	return (str);
}

void	ft_init_sigint(void)
{
	struct sigaction sa;

	sa.sa_handler = &ft_ctrlc;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
}

void	ft_init_sigint_exec(void)
{
	struct sigaction sa;

	sa.sa_handler = &ft_ctrlc_exec;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_init_sigint_hd(void)
{
	struct sigaction sa;

	sa.sa_handler = &ft_ctrlc_hd;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_init_sigquit_exec(void)
{
	struct sigaction sa;

	sa.sa_handler = &ft_ctrlb_exec;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_init_sigquit(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int ac, char **av, char**envp)
{
	char *str;
	t_data data;

	(void)ac;
	(void)av;
	
	ft_init(envp, &data);
	if(isatty(0) == 0)
		data.bool_redir_0 = 1;
	if(isatty(2) == 0)
		data.bool_redir_2 = 1;
	// fprintf(stderr,"%d\n", data.bool_redir_0);
	// if (!data.bool_redir_0 && !data.bool_redir_2)
	// 	ft_logo();
	ft_init_sigint();
	ft_init_sigquit();
	if (!data.bool_redir_0 && !data.bool_redir_2)
		str = ft_prompt();
	else
		str = get_next_line(0);
	add_history(str);
	while (str)
	{
		if (str && str[0])
		{
			str = ft_parse(str, &data);
			if (str && !ft_parse_for_exec(&data))
			{
				ft_pipex(&data);
				ft_close_all(data.pip);
				ft_unlink_hd(&data.exec);
			}
			ft_init_sigint();
			ft_init_sigquit();

		}
		free(str);
		if (!data.bool_redir_0 && !data.bool_redir_2)
			str = ft_prompt();
		else
			str = get_next_line(0);
		add_history(str);
	}
	free(str);
	ft_close(&data.pip.saved_stdin);
	ft_close(&data.pip.saved_stdout);
	ft_free_end(&data);
	if (!data.bool_redir_0 && !data.bool_redir_2)
		write(2,"\nexit\n", 6);
	return (err_value);
}