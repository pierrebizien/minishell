/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export_pt2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:54:23 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/27 21:34:51 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	ft_verif_str_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) == 1 || str[i] == '=' || str[i] == '/' || \
		str[i] == '\0' || str[i] == '+' || str[i] == '$' || (str[0] == '-' && \
			(str[1] == '\0' || str[1] == '\0')))
		return (0);
	while (str[++i] != '=' && str[i] != '+')
	{
		if (is_ws(str[i]) == 1 || str[i] == '\0')
			return (1);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (0);
	if (str[i] == '=')
		return (2);
	if (str[i] == '+')
		return (3);
	return (1);
}

int	ft_verif_option_export(char **cmd, char **cmd_quotes)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd_quotes[i][0] == 1)
			i++;
		else if (cmd[i][0] == '-')
			return (ft_putstr_fd("export: usage: export \
[name[=value] ...] (no option)\n", 2), 1);
		else
			i++;
	}
	return (0);
}

void	ft_export_putstr(char *cmd)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
