/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pc_id.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:46:43 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 01:05:25 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

void	ft_putchar_pc_idu(char c)
{
	c = c + 48;
	write(1, &c, 1);
}

void	ft_putnbr_pc_id(int nb)
{
	if (nb < -2147483647)
	{
		write(1, "-", 1);
		write(1, "2147483648", 10);
		return ;
	}	
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}	
	if (nb < 10)
		ft_putchar_pc_idu(nb);
	else
	{
		ft_putnbr_pc_id(nb / 10);
		ft_putnbr_pc_id(nb % 10);
	}
}

int	ft_pc_id(int nbr, int nbrch)
{
	ft_putnbr_pc_id(nbr);
	if (nbr < -2147483647)
		return (nbrch + 11);
	if (nbr <= 0)
	{
		nbrch++;
		nbr = -nbr;
	}
	while (0 < nbr)
	{
		nbr = nbr / 10;
		nbrch++;
	}
	return (nbrch);
}
