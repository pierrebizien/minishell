/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 09:19:39 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_err_value;

static int	is_sep_4(char c, char *sep)
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

static size_t	count_words_4(char const *s, char *sep)
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

static void	fill_tab_4(char *new, char const *s, int len)
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

void	free_tabstr_4(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	set_mem_4(char **tab, char const *s, char *sep, t_split	*split)
{
	int		dq;
	int		sq;

	split->index = 0;
	split->i = 0;
	dq = -1;
	sq = -1;
	while (s && s[split->index])
	{
		split->count = 0;
		ft_maj_quotes(&dq, &sq, s[split->index]);
		while (s[split->index + split->count] && (dq == 1 || sq == 1 || \
			(!is_sep_4(s[split->index + split->count], sep))))
		{
			split->count++;
			if (s[split->index + split->count] == '\'' || s[split->index + split->count] == '"')
				ft_maj_quotes(&dq, &sq, s[split->index + split->count]);
		}
		if (split->count > 0)
		{
			tab[split->i] = malloc(sizeof(char) * (split->count + 1));
			if (!tab[split->i])
				return (free_tabstr_4(tab), 0);
			fill_tab_4(tab[split->i], (s + split->index), split->count);
			split->i++;
			split->index = split->index + split->count;
		}
		else
			split->index++;
	}
	tab[split->i] = 0;
	return (0);
}

char	**ft_split_lq(char const *s, char *sep)
{
	size_t	words;
	t_split	split;
	char	**tab;

	words = count_words_4(s, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem_4(tab, s, sep, &split);
	return (tab);
}
