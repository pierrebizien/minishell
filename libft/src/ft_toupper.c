/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:07:10 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_toupper( int character )
{
	if ('a' <= character && character <= 'z')
	{
		return (character - 32);
	}
	return (character);
}

// int main(void)
// {
// 	int i = -2;
// 	printf("%c \t", toupper(i));
//     printf("%c \t\t\t %c\n", ft_toupper(i),i);
// 	while (i<130)
// 	{
//         printf("%c \t", toupper(i));
//     	printf("%c \t \n", ft_toupper(i));
// 		i++;
// 	}
// }
