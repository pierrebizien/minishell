/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep_pt0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 08:47:08 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_err_value;

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

int	set_mem_2_if(char **tab, char const *s, char *sep, t_split	*split)
{
	tab[split->i] = malloc(sizeof(char) * (split->count + 1));
	if (!tab[split->i])
		return (free_tabstr_2(tab), 0);
	fill_tab_2(tab[split->i], (s + split->index), sep);
	split->i++;
	split->index = split->index + split->count;
	return (1);
}

int	set_mem_2_else(char **tab, char const *s, t_split	*split)
{
	tab[split->i] = malloc(sizeof(char) * (3));
	if (!tab[split->i])
		return (free_tabstr_2(tab), 0);
	tab[split->i][0] = s[split->index];
	tab[split->i][1] = '\0';
	split->index++;
	split->i++;
	return (1);
}

int	set_mem_2(char **tab, char const *s, char *sep, t_split	*split)
{
	split->index = 0;
	split->i = 0;
	while (s[split->index])
	{
		split->count = 0;
		while (s[split->index + split->count] && \
			!is_sep(s[split->index + split->count], sep))
			split->count++;
		if (split->count > 0)
		{
			if (set_mem_2_if(tab, s, sep, split) == 0)
				return (0);
		}
		else if (is_sep(s[split->index], sep))
		{
			if (set_mem_2_else(tab, s, split) == 0)
				return (0);
		}
		else
			split->index++;
	}
	tab[split->i] = 0;
	return (0);
}

char	**ft_split_k(char const *s, char *sep)
{
	t_split	split;
	size_t	words;
	char	**tab;

	words = count_words_2(s, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem_2(tab, s, sep, &split);
	return (tab);
}
