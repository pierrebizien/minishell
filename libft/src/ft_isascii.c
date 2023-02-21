/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:30:41 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_isascii(int str)
{	
	if (!(-1 < str && str < 128))
		return (0);
	return (1);
}

/*int main(void)
{
	int i = -4;
	while (i<130)
	{
		printf("%d \t", isascii(i));
		printf("%d \t %c\n", ft_isascii(i),i);
		i++;
	}
}*/
