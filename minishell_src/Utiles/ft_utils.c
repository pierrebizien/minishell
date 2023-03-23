/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:55:45 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 12:48:23 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		i++;
	}
	return (i);
}

char	*ft_put_str_in_str(char *dest, char *src, int ind)
{
	int		i;
	size_t	len;
	char	*output;
	size_t	j;
	int		k;

	len = ft_strlen(dest) + ft_strlen(src);
	output = malloc(sizeof(char) * len + 1);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (j < len)
	{
		if (ind == i && src && src[k])
			output[j++] = src[k++];
		else
			output[j++] = dest[i++];
	}
	output[j] = '\0';
	return (output);
}

int	ft_strlen_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

void	ft_close(int *fd)
{
	if (*fd == -1 || *fd == 1 || *fd == 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	ft_print_dargs(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		printf("|%s| \n", strstr[i]);
		i++;
	}
}

char	**ft_join_dstr(char **dest, char *src)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_strstrlen(dest) + 2));
	if (!tmp)
		return (NULL);
	while (dest && dest[i])
	{
		tmp[i] = ft_strdup(dest[i]);
		if (!tmp[i])
			return (ft_free_dchar(tmp), NULL);
		i++;
	}
	tmp[i] = ft_strdup(src);
	if (!tmp[i])
		return (ft_free_dchar(tmp), NULL);
	i++;
	tmp[i] = 0;
	ft_free_dchar(dest);
	return (tmp);
}
