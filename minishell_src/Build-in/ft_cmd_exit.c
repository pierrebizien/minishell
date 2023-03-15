#include "../_Include/minishell.h"


int	ft_exit(char **cmd, t_data *data)
{
	int i;
	int good_exit;

	i = 0;
	if (ft_strstrlen(cmd) == 1)
		exit(data->last_err_num);
	good_exit = 1;
	while (cmd[1][i])
	{
		if(ft_isdigit(cmd[1][i]) == 0)
			good_exit = 0;
		i++;
	}
	if (good_exit == 0)
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(cmd[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(2);

	}
	else if (ft_strstrlen(cmd) == 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 1);
		return (1);
	}
	else
	{
		good_exit = ft_atoi(cmd[1]);
		exit((unsigned char) good_exit);
	}
	return (0);
}



// exit 1 b
// exit 1 1
// exit b b
// exit 1b b