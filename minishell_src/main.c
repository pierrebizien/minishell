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
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	str = readline("\e[33;1mminishell> \e[0m");

	add_history(str);
	while (str)
	{
		if (str && str[0])
			str = ft_parse(str);
		// ft_check();
		ft_pipex();
		ft_print_args();
		free(str);
		str = readline("\e[36;1mminishell> \e[0m");
		add_history(str);
	}
	printf("\nexit\n");
	return (0);
}