#include "minishell.h"

int	main(int ac, char **av, char**envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	int a;
	char *logo= "	\n /██      /██ /██████ /██   /██ /██████  /██████  /██   /██ /████████ /██       /██      \
					\n| ███    /███|_  ██_/| ███ | ██|_  ██_/ /██__  ██| ██  | ██| ██_____/| ██      | ██      \
					\n| ████  /████  | ██  | ████| ██  | ██  | ██  \\__/| ██  | ██| ██      | ██      | ██      \
					\n| ██ ██/██ ██  | ██  | ██ ██ ██  | ██  |  ██████ | ████████| █████   | ██      | ██      \
					\n| ██  ███| ██  | ██  | ██  ████  | ██   \\____  ██| ██__  ██| ██__/   | ██      | ██      \
					\n| ██\\  █ | ██  | ██  | ██\\  ███  | ██   /██  \\ ██| ██  | ██| ██      | ██      | ██      \
					\n| ██ \\/  | ██ /██████| ██ \\  ██ /██████|  ██████/| ██  | ██| ████████| ████████| ████████\
					\n|__/     |__/|______/|__/  \\__/|______/ \\______/ |__/  |__/|________/|________/|________ ";
	fprintf(stderr, "%s", logo);
	fprintf(stderr, "\n\n\n\n\n\n\n");
	while (1)
	{
		logo = "coucou";
		write(1, "microshell> ", 11);
		write(1, "minishell> ", 11);
		get_next_line(0);
		
	}

	int b;
	//test
}