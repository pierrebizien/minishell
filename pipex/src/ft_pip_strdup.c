/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip_strdup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:08:04 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/21 17:46:36 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  The  strdup()  function returns a pointer to a new string which is a 
//  duplicate of the string s.  Memory for the new string is ob‐
//  tained with malloc(3), and can be freed with free(3).

#include "./inc/pipex_bonus.h"
#include <stdio.h>

char	*ft_p_strdup(const char *s)
{
	char	*str_dup;

	str_dup = ft_p_calloc((ft_p_strlen(s) + 1), sizeof(char));
	if (!str_dup)
		return (NULL);
	ft_p_memcpy(str_dup, s, (int)ft_p_strlen(s));
	return (str_dup);
}

/*
int	main()
{
	char str[] = "Hello my maaaan";
	char *str2;

	str2 = ft_p_strdup(str);
	printf("%s", str2);
}*/