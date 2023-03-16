#include "../_Include/minishell.h"


int	ft_verif_good_exit_signe(char *str)
{
	int i;
	char nbr[20] = "_9223372036854775807";

	if (20 < ft_strlen(str))
		return (1);
	if (ft_strlen(str) < 20)
		return (0);
	i = 1;
	while (str[i])
	{
		if (i == 19 && str[0] == '-' && str[i] <= (nbr[i] + 1) )
			return (0);
		else if (i == 19 && str[0] == '-' && str[i] > (nbr[i] + 1))
			return (1);
		else if (str[i] == nbr[i])
			i++;
		else if (str[i] < nbr[i])
			return (0);
		else if (str[i] > nbr[i])
			return (1);
	}
	return (0);
}

int	ft_verif_good_exit(char *str)
{
	int i;
	char nbr[19] = "9223372036854775807";
	if (str[0] == '-' || str[0] == '+')
		return (ft_verif_good_exit_signe(str));
	if (19 < ft_strlen(str))
		return (1);
	if (ft_strlen(str) < 19)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == nbr[i])
			i++;
		else if (str[i] < nbr[i])
			return (0);
		else if (str[i] > nbr[i])
			return (1);
	}
	return (0);
}

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
		if(ft_isdigit(cmd[1][i]) == 0 && cmd[1][i] != '-' && cmd[1][i] != '+')
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
	else if (ft_verif_good_exit(cmd[1]) == 1)
	{
		fprintf(stderr, "error\n\n");
		exit(2);
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