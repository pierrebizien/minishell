/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 00:54:03 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_err_value;

static int	is_sep(char c, char *sep)
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

static size_t	count_words_2(char const *s, char *sep)
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

static void	fill_tab_2(char *new, char const *s, char *sep)
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

void	free_tabstr_2(char **tab)
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

static int	set_mem_2_pt2(char **tab, char const *s, int i, int index)
{
	tab[i] = malloc(sizeof(char) * (3));
	if (!tab[i])
		return (free_tabstr_2(tab), 0);
	tab[i][0] = s[index];
	tab[i][1] = '\0';
	index++;
	i++;
	return (1);
}
static void	set_mem_2_pt3(char *sep, char const *s, int index, int count)
{
	
	while (s[index + count] && !is_sep(s[index + count], sep))
		count++;
}

static int	set_mem_2_pt4(char **tab, int i, int count)
{
	tab[i] = malloc(sizeof(char) * (count + 1));
	if (!tab[i])
		return (free_tabstr_2(tab), 0);
	return (1);
}

static void	set_mem_2(char **tab, char const *s, char *sep, int count)
{
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		set_mem_2_pt3(sep, s, index, count);
		if (count > 0)
		{
			if (set_mem_2_pt4(tab, i, count) == 0)
				return ;
			fill_tab_2(tab[i], (s + index), sep);
			i++;
			index = index + count;
		}
		else if (is_sep(s[index], sep))
		{
			if (set_mem_2_pt2(tab, s, i, index) == 0)
				return ;
		}
		else
			index++;
	}
}

char	**ft_split_k(char const *s, char *sep)
{
	size_t	words;
	size_t	count;
	char	**tab;

	count = 0;
	words = count_words_2(s, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab[words] = 0;
	set_mem_2(tab, s, sep, count);
	return (tab);
}
