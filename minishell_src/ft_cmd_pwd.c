#include "./inc/minishell.h"

int	ft_pwd(t_data *data)
{
	(void)data;
	ft_putstr_fd(getcwd(NULL, 0), 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
