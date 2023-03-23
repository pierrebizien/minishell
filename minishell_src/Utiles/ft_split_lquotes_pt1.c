/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lquotes_pt1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 10:25:00 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_err_value;

int	is_sep_4(char c, char *sep)
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

size_t	count_words_4(char const *s, char *sep)
{
	size_t	words;
	size_t	i;
	int		sq;
	int		dq;

	words = 0;
	i = 0;
	sq = -1;
	dq = -1;
	while (s && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			if (i <= 0 || s[i - 1] != '\\')
				ft_maj_quotes(&dq, &sq, s[i]);
		if ((dq == -1 && sq == -1) && (!is_sep_4(s[i], sep) && \
			(is_sep_4(s[i + 1], sep) || s[i + 1] == '\0')))
			words++;
		i++;
	}
	return (words);
}

void	fill_tab_4(char *new, char const *s, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}
