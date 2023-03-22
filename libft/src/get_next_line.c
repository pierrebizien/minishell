/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:30:09 by tchevrie          #+#    #+#             */
/*   Updated: 2023/03/22 14:56:02 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/get_next_line.h"

int	ft_s(char *str, int verif)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n' && verif == 1)
		i++;
	return (i);
}

char	*ft_my_malloc(char *buffer, char *ligne, int size)
{
	int		i;
	int		j;
	char	*upligne;

	i = 0;
	j = 0;
	if (buffer[i] == '\0')
		return (ligne);
	while (buffer[i] == -42)
		i++;
	upligne = malloc(sizeof(char) * (ft_s(ligne, 1) + ft_s(&buffer[i], 1) + 2));
	if (upligne == NULL)
		return (NULL);
	upligne[ft_s(ligne, 1) + ft_s(&buffer[i], 1)] = '\0';
	size = ft_s(ligne, 1);
	while (--size + 1)
	{
		upligne[j] = ligne[j];
		j++;
	}
	upligne = ft_dup_upligne(upligne, buffer, i, j);
	free(ligne);
	return (upligne);
}

char	*ft_new_line(char *buffer, int size, int fd)
{	
	char	*ligne;

	ligne = malloc(sizeof(char));
	if (ligne == NULL)
		return (NULL);
	ligne[0] = '\0';
	while (size != 0)
	{
		ligne = ft_my_malloc(buffer, ligne, size);
		if (ligne == NULL)
			return (free(ligne), NULL);
		if (ligne[ft_s(ligne, 0)] == '\n')
			return (ligne);
		size = read(fd, buffer, BUFFER_SIZE);
	}
	if (ligne[0] == '\0')
	{
		free(ligne);
		return (NULL);
	}
	return (ligne);
}

char	*get_next_line(int fd)
{
	int			size;
	static char	buffer[BUFFER_SIZE + 1] = {0};

	size = -5;
	buffer[BUFFER_SIZE] = '\0';
	if (buffer[0] == '\0')
		size = read(fd, buffer, BUFFER_SIZE);
	if (size == 0 || size == -1)
		return (NULL);
	return (ft_new_line(buffer, size, fd));
}
