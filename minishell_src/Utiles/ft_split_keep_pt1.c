/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_pt1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 16:14:33 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_err_value;

int	is_sep(char c, char *sep)
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

size_t	count_words_2(char const *s, char *sep)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep(s[i], sep) && (is_sep(s[i + 1], sep) || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (2 * words - 1);
}

void	fill_tab_2(char *new, char const *s, char *sep)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_sep(s[i], sep))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}
