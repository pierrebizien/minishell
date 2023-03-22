/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_lq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:23:06 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 00:25:26 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_begin(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	int		in_set;

	in_set = 0;
	i = 0;
	j = 0;
	while (s1[i])
	{
		in_set = 0;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				if (i <= 0 || s1[i - 1] != '\\')
					in_set = 1;
			j++;
		}
		if (!in_set)
			break ;
		i++;
	}
	return ((char *) s1 + i);
}

static char	*find_end(char const *s1, char const *set, char const *begin)
{
	size_t	i;
	size_t	j;
	int		in_set;

	in_set = 0;
	i = ft_strlen(s1) - 1;
	j = 0;
	while (s1 + i >= begin)
	{
		in_set = 0;
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				if (i <= 0 || s1[i - 1] != '\\')
					in_set = 1;
			j++;
		}
		if (!in_set)
			break ;
		i--;
	}
	if (s1 + i < begin)
		return ((char *) begin);
	return ((char *) s1 + i);
}

static char	*fill_str(char const *begin, char const *end)
{
	char	*new;
	size_t	i;

	new = malloc(sizeof(char) * (end - begin + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (begin + i <= end)
	{
		new[i] = begin[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strtrim_lq(char const *s1)
{
	char		*begin;
	char		*end;
	char		*new;
	const char	set[] = "\"'";

	begin = find_begin(s1, set);
	end = find_end(s1, set, s1);
	if (!s1[0] || end < begin)
	{
		new = malloc(sizeof(char) * 1);
		if (!new)
			return (NULL);
		new[0] = '\0';
	}
	else
		new = fill_str(begin, end);
	if (!new)
		return (NULL);
	return (new);
}
