/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:55:45 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 16:18:10 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

char	**ft_join_dstr(char **dest, char *src)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_strstrlen(dest) + 2));
	if (!tmp)
		return (NULL);
	while (dest && dest[i])
	{
		tmp[i] = ft_strdup(dest[i]);
		if (!tmp[i])
			return (ft_free_dchar(tmp), NULL);
		i++;
	}
	tmp[i] = ft_strdup(src);
	if (!tmp[i])
		return (ft_free_dchar(tmp), NULL);
	i++;
	tmp[i] = 0;
	ft_free_dchar(dest);
	return (tmp);
}
