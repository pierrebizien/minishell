/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:27:41 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/24 10:51:23 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (!(str[i] == '\0'))
	{
		i++;
	}
	return (i);
}
size_t	ft_strlen_WS(const char *str)
{
	size_t	i;

	i = 0;
	while (!(str[i] == '\0'))
		i++;
	return (i);
}
