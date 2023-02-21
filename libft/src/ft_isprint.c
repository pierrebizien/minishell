/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:32:56 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_isprint(int str)
{	
	if (!(31 < str && str < 127))
		return (0);
	return (1);
}

/*int main(void)
{
	int i = -2;
	while (i<129)
	{
		printf("%d \t", isprint(i));
		printf("%d \t %c\n", ft_isprint(i),i);
		i++;
	}
}*/
