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
	int len;
	int j;
	int k;
	char *str;

	i = -1;
	j = 0;
	len = 0;
	while (tab[++i])
		len += ft_strlen(tab[i]);
	len += i - 1;
	fprintf(stderr, "len of str = %d\n\n", len);
	str = ft_calloc(sizeof(char) , len + 1);
	if (!str)
		return (NULL);
	i = -1;
	k = -1;
	while (tab[++i])
	{
		j = -1;
		while(tab[i][++j])
			str[++k] = tab[i][j];
		// fprintf(stderr, "1str in fonct = \t|%s|\t k =%d/%d\n", str,k, len);
		if (k < len - 1)
		{
			str[++k] = sep;
			fprintf(stderr, "ici\n\n");
		}
		fprintf(stderr, "2str in fonct = \t|%s|(%d)\n", str, str[k + 1]);
	}
	str[k] = '\0';
	return (str);
}