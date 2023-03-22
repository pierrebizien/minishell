/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:45:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 19:10:07 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_verif_good_exit_signe(char *str)
{
	int			i;
	const char	nbr[20] = "_9223372036854775807";

	if (20 < ft_strlen(str))
		return (1);
	if (ft_strlen(str) < 20)
		return (0);
	i = 1;
	while (str[i])
	{
		if (i == 19 && str[0] == '-' && str[i] <= (nbr[i] + 1))
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
	int			i;
	const char	nbr[19] = "9223372036854775807";

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

void	ft_free_before_exit(char **cmd, t_data *data, char **cmd_quotes)
{
	free(data->oldpwd);
	free(data->pwd);
	ft_free_dchar(cmd);
	ft_free_dchar(cmd_quotes);
	ft_free_env(data);
	ft_free_list(&data->exec);
	ft_close_all(data->pip, data);
	ft_free_dchar(data->to_free.env_tab);
	ft_free_dchar(data->to_free.paths_env);
	free(data->to_free.path_exec);
	(void) data;
}

int	ft_exit_bis(char **cmd, t_data *data, char **cmd_quotes, int good_exit)
{
	if (good_exit == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_before_exit(cmd, data, cmd_quotes);
		exit(2);
	}
	else if (ft_strstrlen(cmd) == 3)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 2);
	else if (ft_verif_good_exit(cmd[1]) == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_before_exit(cmd, data, cmd_quotes);
		exit(2);
	}
	else
	{
		good_exit = ft_atoi(cmd[1]);
		ft_free_before_exit(cmd, data, cmd_quotes);
		exit((unsigned char) good_exit);
	}
	return (0);
}

int	ft_exit(char **cmd, t_data *data, char **cmd_quotes)
{
	int		i;
	int		good_exit;
	char	*tmp;

	i = 0;
	if (ft_strstrlen(cmd) == 1)
	{
		ft_free_before_exit(cmd, data, cmd_quotes);
		exit(g_err_value);
	}
	good_exit = 1;
	tmp = ft_strtrim(cmd[1], " ");
	free(cmd[1]);
	cmd[1] = tmp;
	while (cmd[1][i])
	{
		if (ft_isdigit(cmd[1][i]) == 0 && cmd[1][i] != '-' && cmd[1][i] != '+')
			good_exit = 0;
		i++;
	}
	return (ft_exit_bis(cmd, data, cmd_quotes, good_exit));
}
