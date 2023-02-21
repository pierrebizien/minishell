/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:09:55 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_tolower(int character)
{
	if (64 < character && character < 91)
	{
		return (character + 32);
	}
	return (character);
}

// int main(void)
// {
// 	int i = -2;
// 	while (i<130)
// 	{
//         printf("%c \t", tolower(i));
//     	printf("%c \t %c\n", ft_tolower(i),i);
// 		i++;
// 	}
// }
