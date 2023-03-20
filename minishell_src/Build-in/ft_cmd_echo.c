#include "../_Include/minishell.h"




int ft_verif_nl_echo(char **cmd)
{
	int i;
	int j;
	int last;

	last = 0;
	i = 1;
	while (cmd && cmd[i] && cmd[i][0] == '-')
	{
		fprintf(stderr, "i = %d\n",i);
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			return (i);
		i++;
	}
		fprintf(stderr, "i = %d\n",i);
	return (i);
}

int	ft_echo(char **cmd, char **cmd_quotes)
{
	int i;
	// int j;
	int nl;
	ft_print_dchar(cmd);
	ft_print_dchar(cmd_quotes);
	nl = 1;
	i = ft_verif_nl_echo(cmd);
	if (1 < i)
		nl = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);	
}
// int main(void)
// {
// 	char *test;

// 	test = "echo";
// 	fprintf(stderr, "|");
// 	ft_echo(test);
// 	fprintf(stderr, "|");

// 	test = "echo test";
// 	fprintf(stderr, "|");
// 	ft_echo(test);
// 	fprintf(stderr, "|");

// 	test = "echo -n test";
// 	fprintf(stderr, "|");
// 	ft_echo(test);
// 	fprintf(stderr, "|");
	
// 	test = "echo -nnnnnn -n -nnnnnnnnd Bonjour les amis";
// 	fprintf(stderr, "|");
// 	ft_echo(test);
// 	fprintf(stderr, "|");

// 	test = "echo -nnnnnnnn -n";
// 	fprintf(stderr, "|");
// 	ft_echo(test);
// 	fprintf(stderr, "|");


// }