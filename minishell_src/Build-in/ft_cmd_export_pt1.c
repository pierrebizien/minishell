/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export_pt1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:54:23 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/22 19:04:42 by pbizien          ###   ########.fr       */
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
