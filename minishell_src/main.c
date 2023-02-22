#include "./inc/minishell.h"



t_data data;

int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;

	ft_init(av, envp, ac);
	ft_logo();
	
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	str = readline("\e[36;1mminishell> \e[0m");

	// // fprintf(stderr, "str vaut |%s|\n", str);
	add_history(str);
	while (str)
	{
		if (str && str[0])
			ft_parse(str);
		free(str);
		str = readline("\e[36;1mminishell> \e[0m");
		add_history(str);
	}
	// write(1, &str, 10);
	printf("\nexit\n");
	return (0);
	//test
}