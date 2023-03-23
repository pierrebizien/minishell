/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_pt5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 07:35:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/23 15:43:11 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

char	*ft_convert_variable_bis(char **s, t_data *data, int *i)
{
	char	*tmp;
	char	*var;

	var = ft_check_env(*s + *i + 1, data);
	if (!ft_is_hd(*s, *i))
	{
		ft_memmove(*s + *i, *s + *i + ft_strlen_var_env(*s + *i), \
			ft_strlen(*s + *i + ft_strlen_var_env(*s + *i)) + 1);
		tmp = *s;
		*s = ft_put_str_in_str(*s, var, *i);
		if (!*s)
			return (free(var), free(tmp), ft_pb_malloc(data), NULL);
		free(tmp);
	}
	else
		*i = *i + 1;
	free(var);
	return (NULL);
}

char	*ft_convert_variable(char *s, t_data *data)
{
	int	i;
	int	dq;
	int	sq;

	sq = -1;
	dq = -1;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			ft_maj_quotes(&dq, &sq, s[i]);
		if ((sq == 1 || dq == 1) && s[i] == '$' && (s[i + 1] == '"'\
			|| is_ws(s[i + 1]) || s[i + 1] == '\''))
			i++;
		if (s[i] && s[i] == '$' && s[i + 1] && !is_ws(s[i + 1]) && sq == -1)
			ft_convert_variable_bis(&s, data, &i);
		else
			i++;
	}
	return (s);
}

char	*ft_convert_variable_hd_bis(char **s, t_data *data, char *del, int i)
{
	char	*var;
	char	*tmp;

	var = ft_check_env(*s + i + 1, data);
	if (ft_strncmp(del, *s, ft_strlen(*s)))
	{
		ft_memmove(*s + i, *s + i + ft_strlen_var_env(*s + i), \
			ft_strlen(*s + i + ft_strlen_var_env(*s + i)) + 1);
		tmp = *s;
		*s = ft_put_str_in_str(*s, var, i);
		if (!*s)
		{
			g_err_value = MAL_ERCODE;
			return (free(var), free(tmp), ft_pb_malloc(data), NULL);
		}
		free(tmp);
	}
	free(var);
	return (NULL);
}

char	*ft_convert_variable_hd(char *s, t_data *data, char *del)
{
	int		i;
	int		dq;
	int		sq;

	sq = -1;
	dq = -1;
	i = 0;
	while (s && s[i])
	{
		if ((s[i] == '\'' || s[i] == '"'))
			ft_maj_quotes(&dq, &sq, s[i]);
		if (s[i] == '$' && s[i + 1] && !is_ws(s[i + 1]) && sq == -1)
			ft_convert_variable_hd_bis(&s, data, del, i);
		if (s && s[i])
			i++;
	}
	return (s);
}
