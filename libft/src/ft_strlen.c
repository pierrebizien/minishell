/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:27:41 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/24 16:27:44 by nicolasgriv      ###   ########.fr       */
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
