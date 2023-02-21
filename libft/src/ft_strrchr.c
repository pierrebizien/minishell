/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:32:29 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

char	*ft_strrchr(const char *str, int lettre)
{
	int				i;
	unsigned char	ch;	

	i = ft_strlen(str);
	ch = (char) lettre;
	if (str == NULL)
		return (NULL);
	while (i >= 0)
	{
		if (str[i] == ch)
			return ((char *)&str[i]);
		i--;
	}
	return (NULL);
}

//  int main (void)
//  {
//      char *texte = "bonjour";
//     int lettre = 's';
// 	char * empty = (char*)calloc(1, 1);
//     printf("1:|%s|\n", strrchr(texte, lettre));
//     printf("2:|%s|", ft_strrchr(texte, lettre));    
//  }