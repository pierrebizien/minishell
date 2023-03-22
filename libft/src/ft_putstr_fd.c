/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:56:09 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/22 15:57:43 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SuperLibft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
		write(fd, s, ft_strlen(s));
}

// int main()
// {
//     int fd = open("test.txt", O_WRONLY);
// 	ft_putstr_fd("Bonjourssdsadadadsa sdsdsles amis", fd);
// }