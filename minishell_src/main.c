#include "./inc/minishell.h"



t_data data;

int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *str;
	DIR *dir;
	struct dirent *dir_rent;

	ft_init(av, envp, ac);
	ft_logo();
	dir = opendir(".");
	dir_rent = readdir(dir);
	dir_rent = readdir(dir);
	dir_rent = readdir(dir);
	dir_rent = readdir(dir);
	// printf("%d\n", dir_rent->d_type);
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	str = readline("minishell> ");
	add_history(str);
	while (str)
	{
		if (str && str[0])
			ft_parse(str);
		free(str);
		str = readline("minishell> ");
		add_history(str);
	}
	// write(1, &str, 10);
	printf("\nexit\n");
	return (0);
}