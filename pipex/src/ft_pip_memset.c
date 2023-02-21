/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip_memset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:06:49 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/21 18:00:42 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The memset() function fills the first n bytes of the memory area pointed 
// to by s with the constant byte c.

#include "./inc/pipex_bonus.h"


void	*ft_p_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		str[i] = value;
		i++;
	}
	return (str);
}

/*
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    char test[] = "Salut";
    printf("%s\n", test);
    ft_memset(test, 'a', 3);
    printf("%s\n", test);

}*/