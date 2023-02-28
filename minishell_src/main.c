#include "./inc/minishell.h"



t_data data;


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
	while (strstr[i])
	{
		fprintf(stderr, "\ni vaut %d et strstr %s\n", i, strstr[i]);
		i++;
	}
}
int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;

	ft_init(envp);
	ft_logo();
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	str = readline("\e[36;1mminishell> \e[0m");

	add_history(str);
	while (str)
	{
		if (str && str[0])
			str = ft_parse(str);
		// ft_check();
		ft_pipex();
		// ft_test_builtin(data.args[0]);
		// ft_print_args();
		free(str);
		str = readline("\e[36;1mminishell> \e[0m");
		add_history(str);
	}
	printf("\nexit\n");
	return (0);
}