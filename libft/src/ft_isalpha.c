/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:02:07 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_isalpha(int str)
{	
	if (!((64 < str && str < 91) || (96 < str && str < 123)))
		return (0);
	return (1);
}

/*int main(void)
{
	int i = 0;
	while (i<127)
	{
		printf("%d\n", isalpha(i));
		printf("%d\n\n\n", ft_isalpha(i));
		i++;
	}
}*/
