#include "inc/pipex_bonus.h"

char **ft_add_dchar_pos(char **strstr, int ind, char *str)
{
	int	i;
	int j;
	char **output;

	i = 0;
	j = 0;
	output = malloc(sizeof(char *) * (ft_strstrlen(strstr) + 2));
	if (!output)
		return (NULL); //GERER
	while (strstr && strstr[i])
	{
		if (j == ind)
		{
			output[j++] = str;
		}
		else 
		{
			output[j] = ft_strdup(strstr[i]);
			j++;
			i++;
		}
	}
	ft_free_dchar(strstr);
	output[j] = 0;
	return (output);
}

int	contain_chev_out(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '>')
			return (1);
		i++;
	}
	return (0);
	
}