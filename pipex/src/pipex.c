/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:00:29 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/02 14:52:30 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

// char	**ft_get_paths(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_p_strncmp("PATH=", envp[i], 5) == 0)
// 			break ;
// 		i++;
// 	}
// 	if (i == ft_size_dchar(envp))
// 		return (NULL);
// 	return (ft_p_split((envp[i] + 5), ':'));
// }

int	ft_size_dchar(char **strstr)
{
	int	i;

	i = 0;
	if (!strstr)
		return (0);
	while (strstr[i])
	{
		i++;
	}
	return (i);
}

char	**ft_put_bs(char **paths)
{
	int		i;
	char	**output;

	i = 0;
	output = ft_p_calloc(ft_size_dchar(paths) + 2, sizeof(char *));
	if (!output)
		return (NULL);
	while (paths && paths[i])
	{
		output[i] = ft_p_strjoin(paths[i], "/");
		i++;
	}
	output[i] = ft_p_strdup("");
	output[i + 1] = NULL;
	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	if (paths)
		free (paths);
	return (output);
}

int	ft_find_g_path(t_pipex *data, char **param, int n)
{
	int		test;
	int		i;
	char	*str;

	test = -1;
	i = -1;
	while (test == -1 && data->paths[++i])
	{
		str = ft_p_strjoin(data->paths[i], param[0]);
		test = access(str, X_OK);
		free(str);
	}
	if (test == -1)
		return (-1);
	if (n == 1)
		data->npath1 = i;
	else
		data->npath2 = i;
	return (0);
}

int	pipex(int ac, char **av, char **envp)
{
	t_pipex	data;

	// if (ac < 5 || (ac < 6 && ft_p_strncmp(av[1], "here_doc", 8) == 0))
	// 	return (ft_p_putstr_fd("NB D ARGS INVALIDE\n", 2), 1);
	if (ft_init_pipex(av, &data, envp, ac) != 0)
		return (1);
	// if (ft_p_strncmp(av[1], "here_doc", 8) == 0)
	// 	if (ft_heredoc(&data) != 0)
			return (1);
	return (ft_main_suite(&data, av, envp));
}

