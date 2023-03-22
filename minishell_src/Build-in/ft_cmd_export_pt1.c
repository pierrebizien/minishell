/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export_pt1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:54:23 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 19:21:08 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	ft_just_export(t_data *data)
{
	t_env	*tmp;

	tmp = &data->env;
	while (tmp)
	{
		write(1, "export ", 7);
		write(1, tmp->key, ft_strlen(tmp->key));
		write(1, "=\"", 2);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\"\n", 2);
		tmp = tmp->next;
	}
	return (0);
}

size_t	ft_strlen_ws(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_ws(str[i]) == 0)
		i++;
	return (i);
}

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
