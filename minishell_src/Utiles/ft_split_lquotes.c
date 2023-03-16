/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lquotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/16 11:44:11 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int err_value;

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
static void	ft_maj_quotes(int *dq, int *sq, char c)
{
	if (c == '"' && *sq == -1)
		*dq *= -1;
	if (c == '\'' && *dq == -1)
		*sq *= -1;
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
		// fprintf(stderr, "s[%zu[i]] vaut %s et dq vaut %d et sq vaut %d et words %zu\n", i, s + i, dq, sq, words);
		if ((dq == -1 && sq == -1) && (!is_sep_4(s[i], sep) && (is_sep_4(s[i + 1], sep) || s[i + 1] == '\0')))
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

static int	set_mem_4(char **tab, char const *s, char *sep)
{
	size_t	count;
	size_t	index;
	size_t	i;
	int dq;
	int sq;

	index = 0;
	i = 0;
	dq = -1;
	sq = -1;
	while (s && s[index])
	{
		count = 0;
		// fprintf(stderr, "s[%zu] = |%s| dq %d sq %d is sep %d\n", index, s + index, dq, sq, is_sep_4(s[index], sep));
		if (s[index] == '\'' || s[index] == '"')
				ft_maj_quotes(&dq, &sq, s[index]);
		while (s[index + count] && (dq == 1 || sq == 1 || (!is_sep_4(s[index + count], sep))))
		{
			count++;
			if (s[index + count] == '\'' || s[index + count] == '"')
				ft_maj_quotes(&dq, &sq, s[index + count]);
		}
		// fprintf(stderr, "count %zu s vaut %s dq %d sq %d\n", count, s + count + index, dq, sq);
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return (free_tabstr_4(tab), 0);
			fill_tab_4(tab[i], (s + index), count);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = 0;
	return (0);
}

char	**ft_split_lq(char const *s, char *sep)
{
	size_t	words;
	char	**tab;

	words = count_words_4(s, sep);
	// fprintf(stderr, "COUNT WORDS %zu \n", words);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem_4(tab, s, sep);
	return (tab);
}
