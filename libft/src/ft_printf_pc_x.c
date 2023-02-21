/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pc_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:27:16 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:39:04 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

void	ft_print_base_pc_x(unsigned int nbr, char *base)
{
	if (nbr < 16)
		write (1, &base[nbr], 1);
	else
	{
		ft_print_base_pc_x(nbr / 16, base);
		ft_print_base_pc_x(nbr % 16, base);
	}
}

int	ft_pc_x(long nbr, char *base, int nbrch)
{
	unsigned int	nb;

	nb = (unsigned int) nbr;
	ft_print_base_pc_x(nb, base);
	return (ft_len_nbr_pc_x(nb, nbrch));
}

int	ft_len_nbr_pc_x(unsigned int nbr, int nbrch)
{	
	if (nbr == 0)
		return (nbrch + 1);
	while (0 < nbr)
	{
		nbr = nbr / 16;
		nbrch++;
	}
	return (nbrch);
}
