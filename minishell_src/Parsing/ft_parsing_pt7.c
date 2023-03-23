/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 09:59:40 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_mod_in_out_bis_2(t_exec **tmp, int *bool_in)
{
	if ((*tmp)->id == F_DELIMITER || (*tmp)->id == F_DELIMITER_SQ)
	{
		if (*bool_in == 1)
			(*tmp)->id = F_FALSED;
		else
			*bool_in = 1;
	}
	*tmp = (*tmp)->prev;
}

void	ft_mod_in_out_bis(t_exec **tmp, int *bool_out, int *bool_in)
{
	if ((*tmp)->id == F_APPEND)
	{
		if (*bool_out == 1)
			(*tmp)->id = F_FALSEA;
		else
			*bool_out = 1;
	}
	if ((*tmp)->id == F_TRONC)
	{
		if (*bool_out == 1)
			(*tmp)->id = F_FALSET;
		else
			*bool_out = 1;
	}
	if ((*tmp)->id == F_INFILE)
	{
		if (*bool_in == 1)
			(*tmp)->id = F_FALSEI;
		else
			*bool_in = 1;
	}
	ft_mod_in_out_bis_2(tmp, bool_in);
}

int	ft_falsed(t_data *data, t_exec **tmp, int *ret_val)
{
	ft_init_sigint_hd();
	ft_heredoc(data, (*tmp)->str, 0, 0);
	if (g_err_value == 130)
		return (ft_free_list(&data->exec), *ret_val = 1, 1);
	if (g_err_value == MAL_ERCODE)
		return (*ret_val = MAL_ERCODE, MAL_ERCODE);
	ft_init_sigint();
	return (0);
}

int	ft_delimiter(t_data *data, t_exec **tmp, int *ret_val)
{
	ft_init_sigint_hd();
	(*tmp)->hd_filename = ft_heredoc(data, (*tmp)->str, 1, 0);
	if (g_err_value == 130)
		return (ft_free_list(&data->exec), *ret_val = 1, 1);
	if (g_err_value == MAL_ERCODE)
		return (*ret_val = MAL_ERCODE, MAL_ERCODE);
	ft_init_sigint();
	return (0);
}

int	ft_delimiter_sq(t_data *data, t_exec **tmp, int *ret_val)
{
	ft_init_sigint_hd();
	(*tmp)->hd_filename = ft_heredoc(data, (*tmp)->str, 1, 1);
	if (g_err_value == 130)
		return (ft_free_list(&data->exec), *ret_val = 1, 1);
	if (g_err_value == MAL_ERCODE)
		return (*ret_val = MAL_ERCODE, MAL_ERCODE);
	ft_init_sigint();
	return (0);
}
