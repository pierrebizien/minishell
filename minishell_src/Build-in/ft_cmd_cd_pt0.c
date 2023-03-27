/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_cd_pt0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:42:21 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 15:33:38 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"
#include <sys/types.h>
#include <dirent.h>

char	*ft_just_cd(t_data *data)
{
	t_env	*tmp;

	tmp = &data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "HOME", ft_strlen(tmp->key)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_check_if_pwd_change(t_data *data)
{
	char	*chartmp;
	int		verif;

	chartmp = getcwd(NULL, 0);
	verif = ft_strcmp(data->pwd, chartmp);
	free(chartmp);
	return (verif);
}

void	ft_change_pwd(t_data *data)
{
	t_env	*tmp;

	tmp = &data->env;
	if (ft_check_if_pwd_change(data) == 0)
		return ;
	free(data->oldpwd);
	data->oldpwd = ft_strdup(data->pwd);
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(data->pwd);
		}
		if (ft_strncmp(tmp->key, "OLDPWD", ft_strlen(tmp->key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(data->oldpwd);
		}
		tmp = tmp->next;
	}
}

int	ft_cd_pt2(char **str, t_data *data)
{
	char	*path;

	path = NULL;
	if (ft_strstrlen(str) == 1)
	{
		path = ft_just_cd(data);
		if (path == NULL)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		if (chdir(path) != 0)
			return (free(path), perror(NULL), 1);
		free(path);
	}
	return (-42);
}

int	ft_cd(char **str, t_data *data)
{
	int		i;

	if (ft_strstrlen(str) == 1)
	{
		if (ft_cd_pt2(str, data) == 1)
			return (1);
	}
	else
	{
		i = 1;
		if (str[i][0] == '-')
			return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(str[i], 2), \
				ft_putstr_fd(": invalid option", 2), 2);
		if (str[i] == 0)
			return (0);
		if (ft_strstrlen(str) != i + 1)
			return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
		if (chdir(str[i]) != 0)
			return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(str[i], 2), \
				ft_putstr_fd(": ", 2), perror(NULL), 1);
	}
	ft_change_pwd(data);
	return (0);
}
