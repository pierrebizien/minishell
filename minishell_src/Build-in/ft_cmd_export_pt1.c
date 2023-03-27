/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_export_pt1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:54:23 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/27 21:35:44 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

char	**ft_get_env_for_export(t_env *env)
{
	t_env	*tmp;
	char	**output;
	int		k;

	tmp = env;
	k = 0;
	output = malloc(sizeof(char *) * (ft_len_list(env) + 1));
	output[ft_len_list(env)] = 0;
	while (env)
	{
		output[+k] = malloc(sizeof(char) * (ft_strlen(env->key) + \
			ft_strlen(env->value) + 4));
		if (!output[k])
			return (ft_free_dchar(output), NULL);
		ft_memcpy(output[k], env->key, ft_strlen(env->key));
		output[k][ft_strlen(env->key)] = '=';
		output[k][ft_strlen(env->key) + 1] = '"';
		ft_memcpy(output[k] + ft_strlen(env->key) + 2, env->value, \
			ft_strlen(env->value));
		output[k][ft_strlen(env->key) + ft_strlen(env->value) + 2] = '"';
		output[k++][ft_strlen(env->key) + ft_strlen(env->value) + 3] = '\0';
		env = env->next;
	}
	env = tmp;
	return (output);
}

void	ft_sort_strstr_alpha(char **tab)
{
	char	*tmp;
	int		i;

	i = -1;
	while (tab && tab[++i])
	{
		if (tab && tab[i] && tab[i + 1] && ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = -1;
		}
	}
}

int	ft_just_export(t_data *data)
{
	char	**env;
	int		i;

	i = -1;
	env = ft_get_env_for_export(&data->env);
	ft_sort_strstr_alpha(env);
	ft_sort_strstr_alpha(data->just_export);
	while (env[++i])
	{
		write(1, "export ", 7);
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
	i = -1;
	while (data->just_export && data->just_export[++i])
	{
		write(1, "export ", 7);
		write(1, data->just_export[i], ft_strlen(data->just_export[i]));
		write(1, "\n", 1);
	}
	ft_free_dchar(env);
	return (0);
}

size_t	ft_strlen_ws(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_ws(str[i]) == 0)
		i++;
	return (i);
}
