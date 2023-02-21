/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolasgriveau <nicolasgriveau@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:37:48 by nicolasgriv       #+#    #+#             */
/*   Updated: 2023/02/18 11:39:16 by nicolasgriv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

int	ft_writechar(char ch, int nbrch)
{
	write(1, &ch, 1);
	nbrch++;
	return (nbrch);
}

int	ft_writestr(char *str, int nbrch)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_writestr("(null)", nbrch));
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
		nbrch++;
	}
	return (nbrch);
}

int	ft_verif_pc(const char *str)
{
	if (str[1] == 'c')
		return (1);
	else if (str[1] == 's')
		return (1);
	else if (str[1] == 'p')
		return (1);
	else if (str[1] == 'd')
		return (1);
	else if (str[1] == 'i')
		return (1);
	else if (str[1] == 'u')
		return (1);
	else if (str[1] == 'x')
		return (1);
	else if (str[1] == 'X')
		return (1);
	else if (str[1] == '%')
		return (1);
	else
		return (2);
}

int	ft_print_pourcent(const char *str, int nbrch, va_list *list)
{
	if (str[1] == 'c')
		nbrch = ft_writechar(va_arg(*list, int), nbrch);
	if (str[1] == 's')
		nbrch = ft_writestr(va_arg(*list, char *), nbrch);
	if (str[1] == 'p')
		nbrch = ft_pc_p(va_arg(*list, unsigned long), nbrch);
	if (str[1] == 'd')
		nbrch = ft_pc_id(va_arg(*list, int), nbrch);
	if (str[1] == 'i')
		nbrch = ft_pc_id(va_arg(*list, int), nbrch);
	if (str[1] == 'u')
		nbrch = ft_pc_u(va_arg(*list, unsigned int), nbrch);
	if (str[1] == 'x')
		nbrch = ft_pc_x(va_arg(*list, long), "0123456789abcdef", nbrch);
	if (str[1] == 'X')
		nbrch = ft_pc_x(va_arg(*list, long), "0123456789ABCDEF", nbrch);
	if (str[1] == '%')
		nbrch = ft_writechar('%', nbrch);
	return (nbrch);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		nbrch;
	va_list	list;

	i = -1;
	nbrch = 0;
	va_start(list, str);
	if (str == NULL)
		return (-1);
	while (str[++i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == '\0')
			return (-1);
		if (str[i] == '%' && ft_verif_pc(&str[i]) == 2)
			nbrch = ft_writechar('%', nbrch);
		else if (str[i] == '%')
			nbrch = ft_print_pourcent(&str[i++], nbrch, &list);
		else
			nbrch = ft_writechar(str[i], nbrch);
	}
	va_end(list);
	return (nbrch);
}
