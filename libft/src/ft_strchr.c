/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:42:06 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

char	*ft_strchr(char *str, int lettre)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char) lettre;
	while (str[i] != ch)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return (&str[i]);
}
// int main (void)
// {
//     char *texte = "ciuyguyguygciuyguygcd";
//     int lettre = 'g';
//     printf("1:%s\n", strchr("tripoulle", 't' + 256));
//     printf("2:%s", ft_strchr("tripoulle", 't' + 256));    
// }