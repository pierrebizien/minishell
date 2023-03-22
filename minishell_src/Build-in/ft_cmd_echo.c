/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:41:05 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 18:42:58 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	ft_verif_nl_echo(char **cmd)
{
	int	i;
	int	j;
	int	last;

	last = 0;
	i = 1;
	while (cmd && cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(char **cmd, char **cmd_quotes)
{
	int	i;
	int	nl;

	(void)cmd_quotes;
	nl = 1;
	i = ft_verif_nl_echo(cmd);
	if (1 < i)
		nl = 0;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
