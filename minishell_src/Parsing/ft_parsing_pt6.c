/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 10:00:27 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_modif_in_out_first(t_exec **tmp, t_exec *tmpstart)
{
	int		bool_out;
	int		bool_in;

	bool_in = 0;
	bool_out = 0;
	while ((*tmp)->next != NULL && (*tmp)->id != F_PIPE)
		*tmp = (*tmp)->next;
	if ((*tmp)->id == F_PIPE)
		*tmp = (*tmp)->prev;
	while (*tmp != NULL && (*tmp)->id != F_PIPE)
		ft_mod_in_out_bis(tmp, &bool_out, &bool_in);
	*tmp = tmpstart;
	if ((*tmp)->id == F_PIPE && (*tmp)->next != NULL)
		*tmp = (*tmp)->next;
}

int	ft_modif_in_out_ter(t_data *data, t_exec **tmp, int *ret_val)
{
	if ((*tmp)->id == F_FALSED)
	{
		if (ft_falsed(data, tmp, ret_val) != 0)
			return (*ret_val);
	}
	else if ((*tmp)->id == F_DELIMITER)
	{
		if (ft_delimiter(data, tmp, ret_val) != 0)
			return (*ret_val);
	}
	else
	{
		if (ft_delimiter_sq(data, tmp, ret_val) != 0)
			return (*ret_val);
	}
	return (0);
}

int	ft_modif_in_out(t_data *data)
{
	t_exec	*tmp;
	t_exec	*tmpstart;
	int		ret_val;

	tmp = &data->exec;
	ret_val = 0;
	while (tmp != NULL)
	{
		tmpstart = tmp;
		ft_modif_in_out_first(&tmp, tmpstart);
		while (tmp != NULL && tmp->id != F_PIPE)
		{
			if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ \
				|| tmp->id == F_FALSED)
				if (ft_modif_in_out_ter(data, &tmp, &ret_val) != 0)
					return (ret_val);
			tmp = tmp->next;
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
	return (0);
}
