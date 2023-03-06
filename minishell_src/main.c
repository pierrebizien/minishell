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
		// fprintf(stderr, "LOOOOP 1\n");
		if (str && str[0])
		{
			str = ft_parse(str, &data);
			if (str)
			{
				ft_parse_for_exec(&data);
				ft_pipex(&data);
				ft_close_all(data.pip);
			}
		}
		// fprintf(stderr, "LOOOOP 2 str = %s\n", str);
		// ft_pipex();
		// ft_test_builtin(data.args[0]);
		// ft_print_args();
		// free(str);
		// fprintf(stderr, "LOOOOP 2 str vaut %s\n", str);
		// dup2(0, 0);
		// get_next_line(0);
		str = readline("\e[36;1mminishell> \e[0m");
		// fprintf(stderr, "LOOOOP 3 str vaut %s\n", str);
		add_history(str);
	}
	printf("\nexit\n");
	return (0);
}