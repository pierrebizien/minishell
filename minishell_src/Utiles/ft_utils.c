#include "../_Include/minishell.h"

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
	len = ft_strlen(dest) + ft_strlen(src);
	// fprintf(stderr, "len vaut %zu\n", len);
	output = malloc(sizeof(char) * len + 1);
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
	// fprintf(stderr, "LAIZEGUEAU2 j vaut %zu \n", j);
	output[j] = '\0';
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
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = 0;
	k = 0;
	while (tab[i])
	{
		j = 0;
		while(tab[i][j])
		{
			str[k] = tab[i][j];
			j++;
			k++;

		}
		if (k < len)
		{
			str[k] = sep;
			k++;
		}
		i++;
	}
	return (str);
}

int	ft_strlen_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}
