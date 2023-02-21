/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:21:17 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_isdigit(int str)
{	
	if (!((47 < str && str < 58)))
		return (0);
	return (1);
}

/*int main(void)
{
	int i = 0;
	while (i<127)
	{
		printf("%d \t", isdigit(i));
		printf("%d \t %c\n\n", ft_isdigit(i),i);
		i++;
	}
}*/
