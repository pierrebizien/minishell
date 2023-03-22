/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export_pt0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:54:23 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 19:25:33 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

static void	ft_ok_export_bis(char *str, int i, char *var, t_env *tmp)
{
	if (ft_strncmp(var, tmp->key, i) == 0)
	{
		free(tmp->value);
		free(var);
		tmp->value = ft_strdup(str + i);
	}
	else
	{
		tmp->next = ft_lstnew_env();
		tmp = tmp->next;
		tmp->key = var;
		tmp->value = ft_substr(str, i, ft_strlen_ws(str + i));
		tmp->printable = 1;
	}
}

static int	ft_ok_export(char *str, t_data *data, char **cmd_quotes)
{
	t_env	*tmp;
	char	*var;
	int		i;
	int		k;

	(void) cmd_quotes;
	i = 0;
	k = 0;
	while (str[i] != '=')
	{
		if (is_ws(str[i]))
			return (0);
		i++;
	}	
	tmp = &data->env;
	var = ft_substr(str, 0, i);
	while (tmp->next && ft_strncmp(var, tmp->key, i + 1))
		tmp = tmp->next;
	while (str[k + i + 1] && is_ws(str[k + i + 1]) == 0)
		k++;
	i = i + 1;
	ft_ok_export_bis(str, i, var, tmp);
	return (0);
}

static void	ft_p_e_exp_bis(char *str, int i, char *var, t_env *tmp)
{
	char	*tmp_for_join;

	if (ft_strncmp(var, tmp->key, i) == 0)
	{
		tmp_for_join = ft_strjoin(tmp->value, str + i);
		free(tmp->value);
		tmp->value = tmp_for_join;
		free(var);
	}
	else
	{
		tmp->next = ft_lstnew_env();
		tmp = tmp->next;
		tmp->key = var;
		tmp->value = ft_strdup(str + i);
		tmp->printable = 1;
	}
}

static int	ft_plus_egal_export(char *str, t_data *data, char **cmd_quotes)
{
	t_env	*tmp;
	char	*var;
	int		i;
	int		k;

	(void) cmd_quotes;
	i = -1;
	k = 0;
	while (str[++i] != '=' && str[i] != '+' && str[i])
	{
		if (is_ws(str[i]) == 1 || str[i + 1] == '\0')
			return (0);
	}
	if (str[i] == '=')
		return (1);
	tmp = &data->env;
	var = ft_substr(str, 0, i);
	while (tmp->next && ft_strncmp(var, tmp->key, i))
		tmp = tmp->next;
	while (str[k + i + 1] && is_ws(str[k + i + 1]) == 0)
		k++;
	i = i + 2;
	ft_p_e_exp_bis(str, i, var, tmp);
	return (0);
}

int	ft_export(char **cmd, t_data *data, char **cmd_quotes)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	if (ft_verif_option_export(cmd, cmd_quotes))
		return (2);
	if (ft_strstrlen(cmd) == 1)
		return (ft_just_export(data));
	while (cmd[i])
	{
		if (ft_verif_str_export(cmd[i]) == 0)
		{
			ft_export_putstr(cmd[i]);
			error = 1;
		}
		else if (ft_verif_str_export(cmd[i]) == 1)
			ft_putstr_fd("exporting a local variable is not possible\n", 2);
		else if (ft_verif_str_export(cmd[i]) == 2)
			ft_ok_export(cmd[i], data, cmd_quotes);
		else if (ft_verif_str_export(cmd[i]) == 3)
			ft_plus_egal_export(cmd[i], data, cmd_quotes);
		i++;
	}
	return (error);
}
