/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:44:55 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*adresse;
	t_list	*adresseback;

	adresse = *lst;
	if (lst == NULL && *lst == NULL)
		return ;
	while (adresse->next != NULL)
	{
		if ((*del) != NULL)
			(*del)(adresse->content);
		adresseback = adresse;
		adresse = adresse->next;
		free(adresseback);
	}
	if ((*del) != NULL)
		(*del)(adresse->content);
	free(adresse);
	*lst = NULL;
}
