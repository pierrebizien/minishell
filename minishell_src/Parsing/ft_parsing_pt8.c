/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 10:36:10 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

int	ft_verif_pipe_bis(char *str, int *i, int *ret_val)
{
	int	j;

	j = *i - 1;
	while (0 <= j && is_ws(str[j]) == 1)
		j--;
	if (j == -1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
			*ret_val = 0, 0);
	j = *i + 1;
	while (1)
	{
		if (is_ws(str[j]))
			j++;
		else if (str[j] == '\0')
			return (ft_putstr_fd("syntax error near unexpected token\
`newline'\n", 2), *ret_val = 0, 0);
		else
			break ;
	}
	return (1);
}

int	ft_verif_pipe(char *str)
{
	int	i;
	int	dq;
	int	sq;
	int	ret_val;

	i = 0;
	dq = -1;
	sq = -1;
	ret_val = 0;
	while (str && str[i])
	{
		ft_maj_quotes(&dq, &sq, str[i]);
		if (dq != 1 && sq != 1 && str[i] == '|')
		{
			if (ft_verif_pipe_bis(str, &i, &ret_val) != 1)
				return (ret_val);
		}
		i++;
	}
	return (1);
}

int	ft_verif_just_chev_bis(char *str, int i, int *r_val)
{
	int	j;

	j = i + 1;
	while (1)
	{
		if (is_ws(str[j]))
			j++;
		else if (str[j] == '<' || str[j] == '>' || str[j] == '|')
			return (ft_putstr_fd("syntax error near unexpected token `", 2), \
				ft_putchar_fd(str[j], 2), ft_putstr_fd("'\n", 2), *r_val = 0, 0);
		else if (str[j] == '\0')
			return (ft_putstr_fd("syntax error near unexpected token \
`newline'\n", 2), *r_val = 0, 0);
		else
			break ;
	}
	return (1);
}

int	ft_verif_just_chev(char *str)
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
		if (dq != 1 && sq != 1 && ((str[i] == '<' && str[i + 1] != '<') || \
			(str[i] == '>' && str[i + 1] != '>')))
		{
			if (ft_verif_just_chev_bis(str, i, &ret_val) != 1)
				return (ret_val);
		}
		i++;
	}
	return (1);
}
