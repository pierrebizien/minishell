/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 11:08:58 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;


void	ft_clean2(char *str, int *in_sq, int *in_dq, int i)
{
	if (str[i] == '"' && !*in_sq)
	{
		if (i <= 0 || str[i - 1] != '\\')
			*in_dq = ft_in_q(*in_dq);
	}
	else if (str[i] == '\'' && !*in_dq)
		*in_sq = ft_in_q(*in_sq);
}

char *ft_clean3(char *str, t_data *data, int *i)
{
	char	*tmp;
	
	tmp = ft_put_str_in_str(str, " ", ++*i);
	if (!tmp)
		return (free(str), ft_pb_malloc(data), NULL);
	free(str);
	str = tmp;
	return (NULL);
}

int ft_test_clean2(int in_sq, int in_dq, char *str, int i)
{
	if (in_sq == 0 && in_dq == 0 && ((str[i] && str[i] != '<' && \
str[i] != ' ' && str[i + 1] && str[i + 1] == '<') || (str[i] &&\
str[i] != '>' && str[i] != ' ' && str[i + 1] && str[i + 1] == '>')))
		return (1);
	else
		return (0);
}

int ft_test_clean1(int in_sq, int in_dq, char *str, int i)
{
	if (in_sq == 0 && in_dq == 0 && ((str[i] && str[i] == '<' && str[i + 1] \
!= '<' && str[i+1] != ' ' && str[i + 1]) || (str[i] == '>' && \
str[i + 1] != '>' && str[i + 1] != ' ' && str[i + 1])))
		return (1);
	else
		return (0);
}

char	*ft_clean(char *str, t_data *data)
{
	int	i;
	int	in_dq;
	int	in_sq;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (str && str[i])
	{
		ft_clean2(str, &in_sq, &in_dq, i);
		if (!in_dq && !in_sq && is_ws(str[i]) && is_ws(str[i + 1]))
			ft_memmove(str + i, (str + i + 1), ft_strlen(str + i + 1) + 1);
		else if (ft_test_clean2(in_sq, in_dq, str, i))
			ft_clean3(str, data, &i);
		else if (ft_test_clean2(in_sq, in_dq, str, i))
		{
			ft_clean3(str,data, &i);
			i++;
		}
		else
			i++;
	}
	if (in_dq || in_sq)
		return (free(str), write(2, "Quotes error\n", 14), NULL);
	return (str);
}
