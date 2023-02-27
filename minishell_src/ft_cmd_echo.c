#include "./inc/minishell.h"

extern t_data data;


int	ft_echo(char *str)
{
	// fprintf(stderr, "str = |%s|\n", str);
	if (str[5] == '-' && str[6] == 'n')
		ft_putstr_fd(str + 8, 1);
	else
	{
		ft_putstr_fd(str + 5, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
// int main(void)
// {
// 	char *test;

// 	test = "echo";
//     fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_echo(test), test);

// 	test = "echo test";
//     fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_echo(test), test);

// 	test = "echo -n test";
//     fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_echo(test), test);

// }