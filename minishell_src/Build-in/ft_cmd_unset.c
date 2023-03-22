/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:20:05 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 19:45:51 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	ft_unset_pt1(char **str, int *return_value)
{
	int	i;

	if (str && ft_strstrlen(str) == 1)
	{
		*return_value = 0;
		return (0);
	}
	i = 1;
	while (str && str[i])
	{
		if (str[i][0] == '-')
		{
		*return_value = 2;
			return (ft_putstr_fd("unset: usage: unset [name[=value] ...] \
(no option)\n", 2), 2);
		}
		i++;
	}
	return (-42);
}

void	ft_unset_pt2(t_data *data, t_env *before, t_env *tmp)
{
	t_env	*after;

	after = tmp->next;
	free(tmp->key);
	free(tmp->value);
	if (before == NULL)
		data->env = *after;
	else if (after == NULL)
	{
		free(tmp);
		before->next = NULL;
	}
	else
	{
		free(tmp);
		before->next = after;
	}
	return ;
}

int	ft_unset(char **str, t_data *data)
{
	int		i;
	t_env	*before;
	t_env	*tmp;

	if (ft_unset_pt1(str, &i) != -42)
		return (i);
	i = 1;
	while (str[i] != 0)
	{
		tmp = &data->env;
		before = NULL;
		while (tmp)
		{
			if (ft_strlen(str[i]) != 0 && ft_strncmp(tmp->key, str[i], \
				ft_strlen(str[i])) == 0)
			{
				ft_unset_pt2(data, before, tmp);
				break ;
			}	
			before = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
