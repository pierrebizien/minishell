#include "./inc/minishell.h"




int ft_verif_nl_echo(char *str)
{
	int i;
	int verif;

	i = 5;
	verif = 0;
	while (str[i])
	{
		if (str[i - 1] != '-' && str[i] == '-' && verif == 0)
			verif = 1;
		else if ((is_ws(str[i]) || (str[i + 1] == '\0' && str[i] == 'n')) && verif == 2)
			return (0);
		else if (str[i] == 'n' && verif <= 2)
			verif = 2;
		else 
			verif = 0;
		i++;
	}
	return (1);
}

int	ft_echo(char **cmd)
{
	int i;
	int nl;
	char *str;

	str = ft_tab_to_str(cmd, ' ');
	i = 5;
	nl = ft_verif_nl_echo(str);
	while (str[i] && (str[i] == '-' || str[i] == 'n' || is_ws(str[i]) == 1))
	{
		if (str[i] == '-' && str[i+1] == '-')
			break ;
		i++;
	}
	while (str[i] && (str[i-1] == '-' || str[i-1] == 'n'))
		i--;
	ft_putstr_fd(str + i, 1);
	if (nl == 1)
	{
		ft_putstr_fd("\n", 1);
	}
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