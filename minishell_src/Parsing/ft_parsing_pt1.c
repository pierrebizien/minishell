/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/27 20:16:06 by ngriveau         ###   ########.fr       */
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
		fprintf(stderr, "tab[%d] = |%s|\n", i, strstr[i]);
		i++;
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
