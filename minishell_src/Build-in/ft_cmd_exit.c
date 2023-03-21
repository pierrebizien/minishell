#include "../_Include/minishell.h"

extern int err_value;


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

int	ft_exit(char **cmd)
{
	int i;
	int good_exit;
	char *tmp;

	i = 0;
	// ft_print_dchar(cmd);
	if (ft_strstrlen(cmd) == 1)
		exit(err_value);
	good_exit = 1;
	tmp = ft_strtrim(cmd[1], " ");
	free(cmd[1]);
	cmd[1] = tmp;
	while (cmd[1][i])
	{
		if (cmd[1][0] == '-' && cmd[1][1] == '-' && cmd[1][2] == '\0')
			good_exit = 1;
		else if (ft_isdigit(cmd[1][1]) == 0 && cmd[1][0] == '-')
			good_exit = 0;
		else if (ft_isdigit(cmd[1][i]) == 0 && cmd[1][i] != '-' && cmd[1][i] != '+')
			good_exit = 0;
		i++;
		// fprintf(stderr, "%dcmd = |%s|%d(%c)\n",good_exit,  cmd[1], ft_isdigit(cmd[1][1]), cmd[1][0]);
	}
	if (good_exit == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);

	}
	else if (ft_strstrlen(cmd) == 3)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (2);
	}
	else if (ft_verif_good_exit(cmd[1]) == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
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