
#include "./inc/SuperLibft.h"
#include <stdio.h>

static int	ft_is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	int				i;
	unsigned int	start;

	i = 0;
	while (s1[i] && ft_is_in_set(s1[i], set))
		i++;
	start = i;
	while (s1[i] && !ft_is_in_set(s1[i], set))
		i++;
	str = ft_calloc(i - start + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1 + start, i - start);
	return (str);
}
