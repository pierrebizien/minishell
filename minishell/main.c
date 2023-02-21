#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


t_data data;

int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;
	// read(0, str, 10);
	ft_init(av, envp, ac);
	ft_logo();
	str = readline("minishell> ");
	fprintf(stderr, "str vaut |%s|\n", str);
	add_history(str);
	while (str != 0)
	{
		str = readline("minishell> ");
		add_history(str);
		ft_parse(str);
	}
	// write(1, &str, 10);

	//test
}