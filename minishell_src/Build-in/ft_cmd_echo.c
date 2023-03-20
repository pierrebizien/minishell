#include "../_Include/minishell.h"




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
	int j;
	int nl;
	char *str;
	str = ft_tab_to_str(cmd, ' ');
	fprintf(stderr, "str = |%s|\n", str);
	i = 5;
	nl = ft_verif_nl_echo(str);
	while (str && str[i] && is_ws(str[i]))
		i++;
	j = i + 1;
	fprintf(stderr, "str[%d] = |%c|\n", i, str[i]);
	while (str && str[i] && str[i] == '-' && str[j] == 'n')
		j++;
	fprintf(stderr, "str[%d] = |%d|\n", j, str[j]);
	if (str[i] != '\0' && is_ws(str[i]) == 0)
	{
		fprintf(stderr, "vrai -n %d\n", is_ws(str[i]));
		i = j;
	}
	fprintf(stderr, "str + i = |%s|\n", str + i);
	
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