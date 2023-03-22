/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:19:45 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 00:20:57 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_unlink_hd(t_exec *begin)
{
	t_exec	*tmp;

	tmp = begin;
	while (tmp)
	{
		if (tmp->hd_filename != NULL)
		{
			unlink(tmp->hd_filename);
		}
		tmp = tmp->next;
	}
}

void	ft_free_list(t_exec *begin)
{
	t_exec	*tmp;

	tmp = begin;
	if (begin)
	{
		free(begin->str);
		free(begin->hd_filename);
		free(begin->quotes);
		begin = begin->next;
	}
	while (begin)
	{
		free(begin->str);
		free(begin->hd_filename);
		free(begin->quotes);
		tmp = begin->next;
		free(begin);
		begin = tmp;
	}
}

void	ft_free_end(t_data *data)
{
	free(data->pwd);
	free(data->oldpwd);
	rl_clear_history();
	ft_free_env(data);
}
