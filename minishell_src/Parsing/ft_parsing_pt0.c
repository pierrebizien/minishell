/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:02:48 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 15:58:38 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

char	*ft_parse(char *str, t_data *data)
{
	char	*tmp;

	str = ft_convert_variable(str, data);
	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (ft_pb_malloc(data), free(tmp), NULL);
	free(tmp);
	str = ft_clean(str, data);
	if (!str || ft_verif_et_ou(str) == 0 || \
	ft_verif_just_chev(str) == 0 || ft_verif_pipe(str) == 0)
	{
		free(str);
		// ft_free_env(data);
		// free(data->pwd);
		// free(data->oldpwd);
		g_err_value = 2;
		return (NULL);
	}
	data->args = ft_split_k(str, "|");
	if (data->args == NULL)
		return (ft_pb_malloc(data), free(str), NULL);
	ft_clean_ws(data);
	return (str);
}
