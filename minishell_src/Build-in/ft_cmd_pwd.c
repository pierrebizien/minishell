#include "../_Include/minishell.h"

int	ft_pwd(char **cmd, t_data *data)
{
	int i;

	i = 0;
	while (cmd && cmd[i])
	{
		if ((cmd[i][0] == '-' && cmd[i][1] == '\0') || (cmd[i][0] == '-' && cmd[i][1] == '-' && cmd[i][2] == '\0'))
			(void) i;
		else if (cmd[i][0] == '-')
			return (ft_putstr_fd("Error pwd: ", 2), ft_putstr_fd(cmd[i], 2), ft_putstr_fd(": invalid option\n", 2), 2);
		i++;
	}
	(void)data;
	ft_putstr_fd(getcwd(NULL, 0), 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
//