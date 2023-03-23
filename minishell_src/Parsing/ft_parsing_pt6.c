/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 08:25:31 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int ft_modif_in_out(t_data *data)
{
	t_exec	*tmp;
	int		bool_out;
	int		bool_in;
	int count_p;
	t_exec	*tmpstart;

	count_p = 0;
	tmp = &data->exec;

	while (tmp != NULL)
	{
		tmpstart = tmp;
		bool_in = 0;
		bool_out = 0;
		while (tmp->next != NULL && tmp->id != F_PIPE)
			tmp = tmp->next;
		if (tmp->id == F_PIPE)
			tmp = tmp->prev;
		while (tmp != NULL && tmp->id != F_PIPE)
		{
			if (tmp->id == F_APPEND)
			{
				if (bool_out == 1)
					tmp->id = F_FALSEA;
				else
					bool_out = 1;
			}
			if (tmp->id == F_TRONC)
			{
				if (bool_out == 1)
					tmp->id = F_FALSET;
				else
					bool_out = 1;
			}
			if (tmp->id == F_INFILE)
			{
				if (bool_in == 1)
					tmp->id = F_FALSEI;
				else
					bool_in = 1;
			}
			if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ)
			{
				if (bool_in == 1)
					tmp->id = F_FALSED;
				else
					bool_in = 1;
			}
			tmp = tmp->prev;
		}
		tmp = tmpstart;
		if (tmp->id == F_PIPE && tmp->next != NULL)
			tmp = tmp->next;
		while (tmp != NULL && tmp->id != F_PIPE)
		{
			if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ || tmp->id == F_FALSED)
			{
				if (tmp->id == F_FALSED)
				{
					ft_init_sigint_hd();
					ft_heredoc(data, tmp->str, 0, 0);
					if (g_err_value == 130)
						return (ft_free_list(&data->exec), 1);
					if (g_err_value == MAL_ERCODE)
						return (MAL_ERCODE);
					ft_init_sigint();
				}
				else if (tmp->id == F_DELIMITER)
				{
					ft_init_sigint_hd();
					tmp->hd_filename = ft_heredoc(data, tmp->str, 1, 0);
					if (g_err_value == 130)
						return (ft_free_list(&data->exec), 1);
					if (g_err_value == MAL_ERCODE)
						return (MAL_ERCODE);
					ft_init_sigint();
				}
				else 
				{
					ft_init_sigint_hd();
					tmp->hd_filename = ft_heredoc(data, tmp->str, 1, 1);
					if (g_err_value == 130)
						return (ft_free_list(&data->exec), 1);
					if (g_err_value == MAL_ERCODE)
						return (MAL_ERCODE);
					ft_init_sigint();
				}
			}
			tmp = tmp->next;
		}
		if (tmp != NULL)
		{
			tmp = tmp->next;
			// count_p ++;
		}
		// fprintf(stderr, "en bas(%d) \t %s\t next = %p\n", tmp->id, tmp->str,tmp->next);

	}
		// ft_print_list(&data->exec);
		return (0);
}