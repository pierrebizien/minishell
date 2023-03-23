/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 07:41:19 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_print_dchar(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		printf("STRSTR VAUT |%s|\n", strstr[i]);
		i++;
	}
}

void	ft_print_list(t_exec *begin)
{
	while (begin)
	{
		fprintf(stderr, "(%d) \t |%s|\n", begin->id, begin->str);
		begin = begin->next;
	}
}

int	is_ws(char c)
{
	int			i;
	const char	ws[] = " \n\t\f\r\v";

	i = 0;
	while (ws[i])
	{
		if (c == ws[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_clean_ws(t_data *data)
{
	int	i;
	int	k;

	i = 0;
	while (data->args && data->args[i])
	{
		if (is_ws(data->args[i][0]))
			ft_memmove(data->args[i], data->args[i] + 1, \
				ft_strlen(data->args[i]));
		k = ft_strlen(data->args[i]);
		if (is_ws(data->args[i][k - 1]))
			data->args[i][k - 1] = '\0';
		i++;
	}
}

void	ft_maj_quotes(int *dq, int *sq, char c)
{
	if (c == '"' && *sq == -1)
		*dq *= -1;
	if (c == '\'' && *dq == -1)
		*sq *= -1;
}
