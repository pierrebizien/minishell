/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:14:53 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*adresse;

	adresse = lst;
	while (adresse->next != NULL)
	{
		(*f)(adresse->content);
		adresse = adresse->next;
	}
	(*f)(adresse->content);
}
