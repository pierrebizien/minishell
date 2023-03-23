/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 08:04:10 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_check_chev_pip(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], \
			"<", ft_strlen(tab[i])))
			if (tab[i + 1] && ft_strlen(tab[i + 1]) != 0 && \
				!ft_strncmp(tab[i + 1], "<", ft_strlen(tab[i + 1])))
				return (1);
		i++;
	}
	return (0);
}

int	ft_check_if_past_is_delim(t_exec *begin, int i)
{
	t_exec	*tmp;
	int		j;

	j = 0;
	(void)i;
	tmp = begin;
	while (tmp && tmp->next && tmp->next->next)
	{
		tmp = tmp->next;
		j++;
	}
	if (tmp && (tmp->id == 4 || tmp->id == 1))
		return (1);
	else
		return (0);
	return (0);
}

int	ft_find_if_hd_quotes(t_data *data, int count_p)
{
	t_exec	*tmp;
	int		len1;
	int		len2;

	tmp = &data->exec;
	(void)count_p;
	len1 = ft_strlen(data->args[count_p]);
	len2 = len1;
	while (len1 - 1)
	{
		if (len1 - 2 >= 0 && data->args[count_p][len1 - 1] == '<' \
			&& data->args[count_p][len1 - 2] == '<')
			if (len1 != len2 && (ft_first_no_chev(data->args[count_p] + len1) \
			== '\'' || ft_first_no_chev(data->args[count_p] + len1) == '"'))
				return (1);
		len1--;
	}
	return (0);
}

char	*ft_clean_quotes(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = -1;
	dq = -1;
	while (str && str[i])
	{
		if ((str[i] == '"' && sq == -1) || (str[i] == '\'' && dq == -1))
		{
			ft_maj_quotes(&dq, &sq, str[i]);
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
		}
		else
			i++;
	}
	return (str);
}

void	ft_clean_list_exec(t_data *data)
{
	t_exec	*tmp;
	t_exec	*before;

	tmp = &data->exec;
	tmp->prev = NULL;
	while (tmp->next != NULL)
	{
		tmp->quotes = malloc(sizeof(char) * 2);
		if (!tmp->quotes)
			return (ft_free_end(data), ft_pb_malloc(data));
		tmp->quotes[0] = '0';
		tmp->quotes[1] = '\0';
		if (tmp->str[0] == '\'' || tmp->str[0] == '"')
			tmp->quotes[0] = '1';
		tmp->str = ft_clean_quotes(tmp->str);
		before = tmp;
		tmp = tmp->next;
		if (tmp != NULL)
			tmp->prev = before;
	}
	tmp = tmp->prev;
	free(tmp->next);
	tmp->next = NULL;
}
