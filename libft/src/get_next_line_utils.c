/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:30:06 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/22 14:56:22 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/get_next_line.h"

char	*ft_dup_upligne(char *upligne, char *buffer, int i, int j)
{
	int	size;

	size = ft_s(&buffer[i], 1);
	while (--size + 1)
	{
		upligne[j] = buffer[i];
		buffer[i] = -42;
		i++;
		j++;
	}
	i = 0;
	while (upligne[i] != '\0')
	{
		if (upligne[i] == -42)
			upligne[i] = '\0';
		i++;
	}
	return (upligne);
}
