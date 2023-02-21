/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_memcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:50:35 by ngriveau          #+#    #+#             */
/*   Updated: 2023/02/21 17:50:54 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:06:00 by pbizien           #+#    #+#             */
/*   Updated: 2022/11/08 09:32:31 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The  memcpy()  function  copies  n  bytes from memory area src to memory
// area dest.  The memory areas must not overlap.  Use mem‐
// move(3) if the memory areas do overlap.

#include "./inc/pipex_bonus.h"

void	*ft_p_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (ptr1);
}

/*
int main()
{

	int dest1[5] = {0};
	int	src[5] = {6,7,8,9,8000000};

	ft_memcpy(dest1, src, sizeof(int) * 5);

	printf("%d ", dest1[0]);
	printf("%d ", dest1[1]);
	printf("%d ", dest1[2]);
	printf("%d ", dest1[3]);
	printf("%d ", dest1[4]);

}*/