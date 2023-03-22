/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:12:15 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 19:13:22 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	ft_pwd(char **cmd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd && cmd[i])
	{
		if ((cmd[i][0] == '-' && cmd[i][1] == '\0') || (cmd[i][0] == '-' && \
			cmd[i][1] == '-' && cmd[i][2] == '\0'))
			(void) i;
		else if (cmd[i][0] == '-')
			return (ft_putstr_fd("Error pwd: ", 2), ft_putstr_fd(cmd[i], 2), \
				ft_putstr_fd(": invalid option\n", 2), 2);
		i++;
	}
	(void)data;
	tmp = getcwd(NULL, 0);
	ft_putstr_fd(tmp, 1);
	free(tmp);
	ft_putstr_fd("\n", 1);
	return (0);
}
