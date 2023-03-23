/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_leave_pt1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 09:05:36 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_err_value;

int	is_sep_3(char c, char *sep)
{
	size_t	i;

	i = 0;
	while (sep && i < ft_strlen(sep))
	{
		if (sep && c == sep[i])
			return (1);
		i++;
	}
	return (0);
}
