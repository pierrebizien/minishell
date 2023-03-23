/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 07:48:29 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_verif_et_ou(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = -1;
	sq = -1;
	while (str && str[i])
	{
		ft_maj_quotes(&dq, &sq, str[i]);
		if (dq != 1 && sq != 1 && str[i] == '&')
			return (ft_putstr_fd("error: unexpected `&'\n", 2), 0);
		else if (dq != 1 && sq != 1 && str[i] == '|' && str[i + 1] == '|')
			return (ft_putstr_fd("error: unexpected `||'\n", 2), 0);
		else
			i++;
	}
	return (1);
}

void	ft_pb_malloc(t_data *data)
{
	ft_free_env(data);
	free(data->oldpwd);
	free(data->pwd);
	ft_putstr_fd("MALLOC ERRRRROR\n", 2);
	exit(MAL_ERCODE);
}

t_exec	*ft_lstnew_pars(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (new == NULL)
		return (NULL);
	new->str = NULL;
	new->id = -42;
	new->next = NULL;
	new->prev = NULL;
	new->hd_filename = NULL;
	return (new);
}

char	ft_first_no_chev(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '<' && !is_ws(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
}

int	ft_count_pipes(t_exec *begin)
{
	int		count;
	t_exec	*tmp;

	tmp = begin;
	count = 0;
	while (begin)
	{
		if (begin->id == F_PIPE)
			count++;
		begin = begin->next;
	}
	return (count);
}
