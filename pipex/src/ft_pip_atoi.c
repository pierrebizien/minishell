/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:02:43 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/21 17:46:36 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The atoi() function converts the initial portion of the string
//        pointed to by nptr to int

#include "./inc/pipex_bonus.h"

long	ft_p_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	count;

	i = 0;
	sign = 1;
	count = 0;
	while (nptr[i] && (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while ((nptr[i] <= '9') && (nptr[i] >= '0') && nptr[i] && count <= INT_MAX)
	{
		count = count * 10 + (nptr[i] - '0');
		i++;
	}
	if (((count >= (long)INT_MAX + 1 && sign == -1) || \
		(count >= (long)INT_MAX && sign == 1)) || (nptr[i] && nptr[i] != ' '))
		return (3147483648);
	return (count * sign);
}

/*

int	main(int ac, char**av)
{
	(void)ac;
	(void)av;
	printf("réelle %d  \n", atoi("\t 4 2"));
	printf("moi %d  \n", ft_p_atoi("\t 4 2"));

}
*/