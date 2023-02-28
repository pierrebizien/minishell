/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:08:11 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/28 15:48:04 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Alloue (avec malloc(3)) et retourne une nouvelle
// chaîne, résultat de la concaténation de s1 et s2.

#include "./inc/pipex_bonus.h"
#include <stdio.h>

char	*ft_p_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*output;
	int		i;
	int		j;

	fprintf(stderr, "MESSIEURS BONSIR\n");
	len = ft_p_strlen(s1) + ft_p_strlen(s2);
	i = 0;
	fprintf(stderr, "MESSIEURS BONJOUR\n");
	output = (char *)ft_p_calloc(len + 1, sizeof(char));
	if (output == NULL)
		return (NULL);
	fprintf(stderr, "MESSIEURS TG\n");
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		output[j] = s2[i];
		i++;
		j++;
	}
	output[j] = '\0';
	fprintf(stderr, "MESSIEURS KFDDJEGJEJ\n");
	return (output);
}

/*
int	main()
{
	char str[] = "Hello";
	char str2[] = "fff";
	char *output;

	output = ft_p_strjoin(str, str2);
	printf("%s", output);
}*/
