#include "./inc/minishell.h"

int	ft_strstrlen(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		i++;
	}
	return (i);	
}

char *ft_put_str_in_str(char *dest, char *src, int ind)
{
	int 	i;
	size_t	len;
	char	*output;
	int		j;
	int		k;

	len = ft_strlen(dest) + ft_strlen(src) + 1;
	output = malloc(sizeof(char) * len);
	if (!output)
		return (NULL); //GERER
	i = 0;
	j = 0;
	k = 0;
	while (dest && dest[i])
	{
		if (ind == i && src && src[k])
			output[j++] = src[k++];
		else
			output[j++] = dest[i++];
	}
	output[j] = '\0';
	return (output);
}