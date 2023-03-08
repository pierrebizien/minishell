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
	size_t		j;
	int		k;

	// fprintf(stderr, "LAIZEGUEA1 dest vaut %s \n", dest);
	len = ft_strlen(dest) + ft_strlen(src) + 1;
	output = malloc(sizeof(char) * len);
	if (!output)
		return (NULL); //GERER
	i = 0;
	j = 0;
	k = 0;
	while (j < len)
	{
		if (ind == i && src && src[k])
			output[j++] = src[k++];
		else
			output[j++] = dest[i++];
	}
	output[j] = '\0';
	// fprintf(stderr, "LAIZEGUEAU2 j vaut %zu \n", j);
	return (output);
}

char *ft_tab_to_str(char **tab, char sep)
{
	int i;
	int j;
	int k;
	char *str;

	i = -1;
	j = 0;
	while (tab[++i])
		j += ft_strlen(tab[i]);
	j += i - 1;
	str = malloc(sizeof(char) * j + 1);
	if (!str)
		return (NULL);
	str[j] = '\0';
	i = -1;
	k = -1;
	while (tab[++i])
	{
		j = -1;
		while(tab[i][++j])
			str[++k] = tab[i][j];
		if (str[k + 1] != '\0')
			str[++k] = sep;
	}
	return (str);
	


}