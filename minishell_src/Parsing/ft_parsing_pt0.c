/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:02:48 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/27 21:29:32 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_verif_ambig_bis(char *str, int i, int *r_val)
{
	int	j;

	j = i - 1;
	while (j >= 0)
	{
		if (is_ws(str[j]))
			j--;
		else if (str[j] == '<' || str[j] == '>')
			return (ft_putstr_fd("ambiguous redirect\n", 2), *r_val = 0, 0);
		else
			break ;
	}
	return (1);
}

int	ft_verif_ambig(char *str)
{
	int	i;
	int	dq;
	int	sq;
	int	ret_val;

	i = 0;
	dq = -1;
	sq = -1;
	while (str && str[i])
	{
		ft_maj_quotes(&dq, &sq, str[i]);
		if (dq != 1 && sq != 1 && str[i] == -1)
		{
			if (ft_verif_ambig_bis(str, i, &ret_val) != 1)
				return (ret_val);
		}
		i++;
	}
	return (1);
}

int	ft_del_fvar_search_chev(char *str, int i)
{
	i--;
	while (0 <= i && str[i])
	{
		if (is_ws(str[i]))
			i--;
		else if (str[i] == '<' || str[i] == '>')
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*ft_del_fvar(char *str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (str && str[i])
	{
		if (i == 0 || str[i] == '|')
			start = i;
		if (str[i] == -1)
		{
			end = i;
			while (str[end] != '|' && str[end] != '\0')
				end++;
			if (ft_del_fvar_search_chev(str, i) == 1)
				ft_memmove(str + start, str + end, ft_strlen(str + end) + 1);
			else
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

char	*ft_parse(char *str, t_data *data)
{
	char	*tmp;

	if (ft_test_neg(str) == 1)
		return (ft_putstr_fd("ASCII over 127\n", 2), NULL);
	str = ft_convert_variable(str, data);
	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (ft_pb_malloc(data), free(tmp), NULL);
	if (str[0] == 0)
		return (free(tmp), free(str), NULL);
	free(tmp);
	str = ft_clean(str, data);
	if (!str || ft_verif_et_ou(str) == 0 || \
	ft_verif_just_chev(str) == 0 || ft_verif_pipe(str) == 0)
		return (free(str), g_err_value = 2, NULL);
	ft_verif_ambig(str);
	str = ft_del_fvar(str);
	if (str && str[0] == '\0')
		return (free(str), NULL);
	data->args = ft_split_lq_k(str, "|");
	if (data->args == NULL)
		return (ft_pb_malloc(data), free(str), NULL);
	ft_clean_ws(data);
	return (str);
}
