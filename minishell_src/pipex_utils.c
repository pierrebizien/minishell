#include "./inc/minishell.h"

void	ft_free_dchar(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

static void    ft_strrjoin_bis(char *new, char const *s3)
{
    size_t    i;

    i = 0;
    while (s3 && s3[i])
    {
        new[i] = s3[i];
        i++;
    }
    new[i] = '\0';
}

char    *ft_strrjoin(char const *s1, char const *s2, char const *s3)
{
    char    *new;
    size_t    i;
    size_t    j;

    if (!s1 && !s2 && !s3)
        return (NULL);
    new = malloc(sizeof(char) * \
        (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
    if (!new)
        return (NULL);
    i = 0;
    while (s1 && s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2 && s2[j])
    {
        new[i + j] = s2[j];
        j++;
    }
    ft_strrjoin_bis(new + i + j, s3);
    return (new);
}