/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 07:44:35 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

size_t	ft_strlen_var_env(char *str)
{
	int	i;

	i = 1;
	if (str && ft_isdigit(str[1]))
		return (2);
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_strlen_ws_quotes(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (is_ws(str[i]) == 0 && str[i] != '"' && str[i] != '\''))
		i++;
	return (i);
}

char	*ft_check_env(char *str, t_data *data)
{
	t_env	*tmp_env;

	tmp_env = &data->env;
	if (str && str[0] == '?')
		return (ft_itoa(g_err_value));
	while (tmp_env)
	{
		if (!strncmp(str, tmp_env->key, ft_strlen_var_env(str)))
			return (ft_strdup(tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

int	ft_is_hd(char *str, int i)
{
	int	j;

	j = 0;
	if (i > 0)
		i--;
	else
		return (0);
	while (str && i >= 0 && (is_ws(str[i]) || str[i] == '"' || str[i] == '\''))
		i--;
	if (i > 0 && str[i] == '<' && str[i - 1] == '<')
		return (1);
	return (0);
}
