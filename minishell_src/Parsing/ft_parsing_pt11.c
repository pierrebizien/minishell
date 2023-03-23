/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt11.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 12:04:42 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_parse_for_e_pipe(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	*count_p = *count_p + 1;
	(*tmp)->id = F_PIPE;
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

int	ft_parse_for_e_infile(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	(void)count_p;
	(*tmp)->id = F_INFILE;
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

int	ft_parse_for_e_tronc(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	(void)count_p;
	(*tmp)->id = F_TRONC;
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

int	ft_parse_for_e_append(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	(void)count_p;
	(*tmp)->id = F_APPEND;
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

int	ft_parse_for_e_del(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	if (ft_find_if_hd_quotes(data, *count_p))
		(*tmp)->id = F_DELIMITER_SQ;
	else
		(*tmp)->id = F_DELIMITER;
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
