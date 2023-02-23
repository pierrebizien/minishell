#include "./inc/minishell.h"



t_data data;


void	ft_print_args(void)
{
	int	i;

	i = 0;
	while (data.args && data.args[i])
	{
		printf("|%s| \n", data.args[i]);
		i++;
	}
	
}

int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;

	ft_init(av, envp, ac);
	ft_logo();
	// printf("%d\n", dir_rent->d_type);
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	str = readline("\e[33;1mminishell> \e[0m");

	// // fprintf(stderr, "str vaut |%s|\n", str);
	add_history(str);
	while (str)
	{
		if (str && str[0])
			str = ft_parse(str);
		ft_print_args();
		free(str);
		str = readline("\e[36;1mminishell> \e[0m");
		add_history(str);
	}
	// write(1, &str, 10);
	printf("\nexit\n");
	return (0);
}