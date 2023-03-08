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
	str = readline("\e[36;1mminishell> \e[0m");
	add_history(str);
	while (str)
	{
		if (str && str[0])
		{
			str = ft_parse(str, &data);
			// fprintf(stderr, "STR MAIN VAUT %s\n", str);
			if (str)
			{
				ft_parse_for_exec(&data);
				ft_pipex(&data);
				ft_close_all(data.pip);
			}
		}
		str = readline("\e[36;1mminishell> \e[0m");
		add_history(str);
	}
	printf("\nexit\n");
	return (0);
}