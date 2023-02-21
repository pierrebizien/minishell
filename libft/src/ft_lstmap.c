/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:46:42 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/18 11:29:52 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*adretour;

	if (!lst || !(*f) || !(*del))
		return (NULL);
	new = ft_lstnew((*f)(lst->content));
	adretour = new;
	while (lst->next != NULL && lst)
	{
		if (!new)
			return (NULL);
		new->next = ft_lstnew((*f)(lst->next->content));
		new = new->next;
		lst = lst->next;
	}
	return (adretour);
}
