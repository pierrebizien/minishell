/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/16 11:44:11 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int err_value;

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
	return (2*words - 1);
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

static int	set_mem_2(char **tab, char const *s, char *sep)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && !is_sep(s[index + count], sep))
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return (free_tabstr_2(tab), 0);
			fill_tab_2(tab[i], (s + index), sep);
			i++;
			index = index + count;
		}
		else if (is_sep(s[index], sep))
		{
			tab[i] = malloc(sizeof(char) * (3));
			if (!tab[i])
				return (free_tabstr_2(tab), 0);
			tab[i][0] = s[index];
			tab[i][1] = '\0';
			index++;
			i++;
		}
		else
			index++;
	}
	tab[i] = 0;
	return (0);
}

char	**ft_split_k(char const *s, char *sep)
{
	size_t	words;
	char	**tab;

	words = count_words_2(s, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem_2(tab, s, sep);
	return (tab);
}
