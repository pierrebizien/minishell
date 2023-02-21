/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pc_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:37:14 by nicolasgriv       #+#    #+#             */
/*   Updated: 2023/02/18 11:38:57 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_pc_p(unsigned long nbr, int nbrch)
{
	if (nbr == 0)
	{
		ft_writestr("(nil)", nbrch);
		return (nbrch + 5);
	}
	nbrch = ft_writestr("0x", nbrch);
	ft_print_pc_p_base(nbr, nbrch);
	return (ft_len_nbr_pc_p(nbr, nbrch));
}

int	ft_print_pc_p_base(unsigned long nbr, int nbrch)
{
	char	*base;

	base = "0123456789abcdef";
	if (nbr < 16)
	{
		nbrch = nbrch + ft_writechar(base[nbr], nbrch);
	}
	else
	{
		ft_print_pc_p_base(nbr / 16, nbrch);
		ft_print_pc_p_base(nbr % 16, nbrch);
	}
	return (nbrch);
}

int	ft_len_nbr_pc_p(unsigned long nbr, int nbrch)
{	
	if (nbr == 0)
		return (1);
	while (0 < nbr)
	{
		nbr = nbr / 16;
		nbrch++;
	}
	return (nbrch);
}
