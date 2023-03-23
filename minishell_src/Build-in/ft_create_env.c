/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:48:06 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 15:50:28 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

t_env	*ft_lstnew_env(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	new->printable = 1;
	return (new);
}

void	ft_modif_shlvl(t_env *tmp)
{
	int	nb;

	nb = ft_atoi(tmp->value);
	free(tmp->value);
	tmp->value = ft_itoa(nb + 1);
}

int	ft_create_env_pt2(char **envp, t_env *tmp, int i)
{
	int		j;
	int		k;

	j = 0;
	while (envp[i][j] != '=' && envp[i][j])
		j++;
	k = 0;
	while (envp[i][k + j + 1])
		k++;
	tmp->key = ft_substr(envp[i], 0, j);
	if (!tmp->key)
		return (1);
	tmp->value = ft_substr(envp[i], j + 1, k);
	if (!tmp->value)
		return (1);
	return (0);
}

int	ft_create_env(char **envp, t_data *data)
{
	int		i;
	t_env	*tmp;

	i = -1;
	tmp = &data->env;
	tmp->key = NULL;
	tmp->printable = 1;
	tmp->value = NULL;
	while (envp[++i])
	{
		if (ft_create_env_pt2(envp, tmp, i) == 1)
			return (1);
		if (ft_strncmp(tmp->key, "SHLVL", 6) == 0)
			ft_modif_shlvl(tmp);
		if (envp[i + 1])
		{
			tmp->next = ft_lstnew_env();
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
	}
	return (0);
}
