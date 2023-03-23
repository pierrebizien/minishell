/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 12:20:44 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;



void	ft_parse_for_e_init(t_data *data, t_exec **tmp, int *j, int *count_p)
{
	free(data->to_free.str);
	*tmp = &data->exec;
	(*tmp)->id = -43;
	(*tmp)->next = NULL;
	(*tmp)->hd_filename = NULL;
	(*tmp)->str = NULL;
	*j = -1;
	*count_p = 0;
}

int	ft_test_loop_1(char *str, char *token)
{
	if (ft_strlen(str) != 0 && !ft_strncmp(str, token, ft_strlen(str)))
		return (1);
	else
		return (0);
}

int	ft_test_loop_2(char *str, int i, char *token)
{
	if (0 < i && str && ft_strlen(str) != 0 && !ft_strncmp(str, token, ft_strlen(str)))
		return (1);
	else
		return (0);
}

void	ft_parse_for_exec_loop(t_data *data, t_exec **tmp, int *count_p, int *i)
{
	if (ft_test_loop_1(data->to_free.tab[*i], "<"))
		i++;
	else if (ft_test_loop_1(data->to_free.tab[*i], "<<"))
		i++;
	else if (ft_test_loop_1(data->to_free.tab[*i], ">"))
		i++;
	else if (ft_test_loop_1(data->to_free.tab[*i], ">>"))
		i++;
	else if (ft_test_loop_1(data->to_free.tab[*i], "|"))
		ft_parse_for_e_pipe(data, tmp, count_p, i);
	else
	{
		if (*i > 0 && ft_test_loop_2(data->to_free.tab[*i - 1], *i, "<"))
			ft_parse_for_e_infile(data, tmp, count_p, i);
		else if (*i > 0 && ft_test_loop_2(data->to_free.tab[*i - 1], *i, "<<"))
			ft_parse_for_e_del(data, tmp, count_p, i);
		else if (*i > 0 && ft_test_loop_2(data->to_free.tab[*i - 1], *i, ">"))
			ft_parse_for_e_tronc(data, tmp, count_p, i);
		else if (*i > 0 && ft_test_loop_2(data->to_free.tab[*i - 1], *i, ">>"))
			ft_parse_for_e_append(data, tmp, count_p, i);
		else
			ft_parse_for_e_cmd(data, tmp, count_p, i);
	}
}

int ft_parse_for_exec(t_data *data)
{
	int i;
	int j;
	int count_p;
	t_exec *tmp;

	ft_parse_for_e_init(data, &tmp, &j, &count_p);
	while (data->args[++j])
	{
		data->to_free.tab = ft_split_lq(data->args[j], " ");
		if (data->to_free.tab == NULL)
			return (ft_pb_malloc(data), -42);
		if (ft_check_chev_pip(data->to_free.tab) == 1)
			return (1);
		i = 0;
		while (data->to_free.tab && data->to_free.tab[i])
		{
			ft_parse_for_exec_loop(data, &tmp, &count_p, &i);
		}
		ft_free_dchar(data->to_free.tab);
	}
	return (ft_parse_for_e_end(data));
}

