#include "./inc/minishell.h"

extern t_data data;

void ft_print_dchar(char **strstr)
{
	int	i;

	i = 0;
	while (strstr && strstr[i])
	{
		printf("STRSTR VAUT |%s|\n", strstr[i]);
		i++;
	}
	
}


int	is_ws(char c)
{
	int	i;
	const char ws[] = " \n\t\f\r\v";

	i = 0;
	while (ws[i])
	{
		if (c == ws[i])
			return (1);
		i++;
	}
	return (0);
	
}

char	*ft_clean(char *str)
{
	int	i;
	int	in_q;

	i = 0;
	in_q = 0;
	while (str && str[i])
	{
		if (str[i] == '"' && in_q == 0)
		{
			in_q = 1;
			i++;
		}
		else if (str[i] == '"' && in_q == 1)
		{
			i++;
			in_q = 0;
		}
		else if (in_q == 0 && is_ws(str[i]) && is_ws(str[i + 1]))
			ft_memmove(str + i, (str + i + 1), ft_strlen(str + i) + 2);
		else
			i++;
	}
	return (str);
}

char *ft_parse(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (free(str), exit(-1), NULL);
	free(tmp);
	str = ft_clean(str);
	
	data.args = ft_split_k(str, "|");
	// printf("str parse vaut |%s|\n", str);
	 return (str);
}

// int ft_detect_cmd(void)
// {
// 	int  count_w;

// 	count_w = 0;
// 	ft_split_mini();

// 	return (0);
// }