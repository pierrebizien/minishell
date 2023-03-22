/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_leave.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 19:10:07 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_err_value;

static int	is_sep_3(char c, char *sep)
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

static size_t	count_words_3(char const *s, char *sep)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (!is_sep_3(s[i], sep) && (is_sep_3(s[i + 1], sep) || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (2*words - 1);
}

static void	fill_tab_3(char *new, char const *s, char *sep)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_sep_3(s[i], sep))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

void	free_tabstr_3(char **tab)
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

static int	set_mem_3(char **tab, char const *s, char *sep)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && !is_sep_3(s[index + count], sep))
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return (free_tabstr_3(tab), 0);
			fill_tab_3(tab[i], (s + index), sep);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = 0;
	return (0);
}

char	**ft_split_l(char const *s, char *sep)
{
	size_t	words;
	char	**tab;

	words = count_words_3(s, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem_3(tab, s, sep);
	return (tab);
}
