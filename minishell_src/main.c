#include "./inc/minishell.h"


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
void	ft_print_dchar(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		fprintf(stderr, "tab[%d] = |%s|\n", i, strstr[i]);
		i++;
	}
	if (!strstr)
		fprintf(stderr, "STRSTR N EXISTE PAS\n");
}


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
	char *str = readline(path);
	return (str);
}


int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;
	t_data data;

	ft_init(envp, &data);
	ft_logo();
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	str = ft_prompt();
	add_history(str);
	while (str)
	{
		signal(SIGINT, ft_ctrlc);
		if (str && str[0])
		{
			fprintf(stderr, "ICIIIII\n");
			str = ft_parse(str, &data);
			if (str)
			{
				ft_parse_for_exec(&data);
				ft_pipex(&data);
				ft_close_all(data.pip);
			}
		}
		str = ft_prompt();
		add_history(str);
	}
	printf("\nexit\n");
	return (0);
}