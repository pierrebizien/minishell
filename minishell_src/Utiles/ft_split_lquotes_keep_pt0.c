/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_lquotes_keep_pt0.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:29:02 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 21:31:43 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_err_value;

int	set_mem_5_if(char **tab, char const *s, t_split *split)
{
	tab[split->i] = malloc(sizeof(char) * (split->count + 1));
	if (!tab[split->i])
		return (free_tabstr_5(tab), 0);
	fill_tab_5(tab[split->i], (s + split->index), split->count);
	split->i++;
	split->index = split->index + split->count;
	return (1);
}

void	set_mem_5_while(char const *s, char *sep, t_split	*split)
{
	while (s[split->index + split->count] && (split->dq == 1 || \
		split->sq == 1 || (!is_sep_5(s[split->index + split->count], sep))))
	{
		split->count++;
		ft_maj_quotes(&split->dq, &split->sq, s[split->index + split->count]);
	}
}

int	set_mem_sep(char **tab, char const *s, char*sep, t_split *split)
{
	(void)s;
	tab[split->i] = malloc(sizeof(char) * (ft_strlen(sep) + 1));
	if (!tab[split->i])
		return (free_tabstr_5(tab), 0);
	fill_tab_5(tab[split->i], sep, ft_strlen(sep));
	split->i++;
	split->index = split->index + ft_strlen(sep);
	return (1);
}

int	set_mem_5(char **tab, char const *s, char *sep, t_split	*split)
{
	split->index = 0;
	split->i = 0;
	split->dq = -1;
	split->sq = -1;
	while (s && s[split->index])
	{
		split->count = 0;
		ft_maj_quotes(&split->dq, &split->sq, s[split->index]);
		set_mem_5_while(s, sep, split);
		if (split->count > 0)
		{
			if (set_mem_5_if(tab, s, split) == 0)
				return (0);
		}
		else if (is_sep_5(s[split->index], sep))
			set_mem_sep(tab, s, sep, split);
		else
			split->index++;
	}
	tab[split->i] = 0;
	return (0);
}

char	**ft_split_lq_k(char const *s, char *sep)
{
	size_t	words;
	t_split	split;
	char	**tab;

	words = count_words_5(s, sep);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem_5(tab, s, sep, &split);
	return (tab);
}
