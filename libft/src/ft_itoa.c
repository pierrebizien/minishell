/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:52:49 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

static char	*ft_nbr_to_str(char *str, int n, int signe, int size)
{
	int	i;

	i = 0;
	if (signe == -1)
	{
		str[i++] = '-';
	}
	while (n > 0)
	{
		str[size] = n % 10 + 48;
		n = n / 10;
		size--;
	}
	return (str);
}

static	char	*ft_itoa_zero(void)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_min_int(int n)
{
	char	*str;

	if (n == 0)
		return (ft_itoa_zero());
	str = malloc(sizeof(char) * 12);
	if (str == NULL)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		signe;
	int		size;
	int		ndb;

	signe = 1;
	size = 0;
	if (n == -2147483648 || n == 0)
		return (ft_min_int(n));
	if (n < 0)
	{
		signe = -1;
		size = 1;
		n = -n ;
	}
	ndb = n;
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	nbr = malloc(sizeof(char) * (size + 1));
	nbr[size] = '\0';
	return (ft_nbr_to_str(nbr, ndb, signe, --size));
}

// int main (void)
// {
// 	printf("%s",ft_itoa(-2147483648));
// }