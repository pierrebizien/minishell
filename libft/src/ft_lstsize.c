/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:44:26 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*adresse;

	i = 1;
	adresse = lst;
	if (lst == 0)
		return (0);
	while (adresse->next != 0)
	{
		adresse = adresse->next;
		i++;
	}
	return (i);
}
