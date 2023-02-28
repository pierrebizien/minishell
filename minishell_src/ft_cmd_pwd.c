#include "./inc/minishell.h"

extern t_data data;

int	ft_pwd(void)
{
	ft_putstr_fd(getcwd(NULL, 0), 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
