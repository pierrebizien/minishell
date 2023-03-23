/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 12:50:50 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_parse_for_e_cmd(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	(void)count_p;
	(*tmp)->id = F_CMD;
	(*tmp)->hd_filename = NULL;
	(*tmp)->str = ft_strdup(data->to_free.tab[*i]);
	(*tmp)->next = ft_lstnew_pars();
	if (!(*tmp)->str || !(*tmp)->next)
		return (ft_free_list(&data->exec), \
		ft_free_dchar(data->to_free.tab), ft_pb_malloc(data), -42);
	*tmp = (*tmp)->next;
	(*tmp)->next = NULL;
	*i = *i + 1;
	return (0);
}

int	ft_parse_for_e_end(t_data *data)
{
	ft_free_dchar(data->args);
	ft_clean_list_exec(data);
	if (ft_modif_in_out(data))
	{
		if (g_err_value == MAL_ERCODE)
			return (ft_free_list(&data->exec), ft_pb_malloc(data), g_err_value);
		return (g_err_value);
	}
	data->pip.nb_pipes = ft_count_pipes(&data->exec);
	return (0);
}
