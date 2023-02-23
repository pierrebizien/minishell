#include "./inc/minishell.h"

extern t_data data;

int ft_1st_chev(void)
{
	
	// if (data.ac == 3)
	 return (0);
}

int ft_detect(void)
{
	 if (data.args && ft_strncmp(data.args[0], "<", ft_strlen(data.args[0])) == 0)
	 {
		  return (ft_1st_chev());
	 }
	 return (0);
}


char *ft_join(char **tmp)
{
	int	i;
	char *str;
	char *tmp2;
	char *tmp3;

	i = 0;
	str = tmp[0];
	while (tmp && tmp[i] && tmp[i + 1])
	{
		tmp3 = str;
		tmp2 = ft_strjoin(tmp3, " ");
		free(tmp3);
		str = ft_strjoin(tmp2, tmp[i + 1]);
		fprintf(stderr, "STR VAUT %s\n", str);
		free(tmp2);
		i++;
	}
	return (str);
	
}

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

int	ft_clean(void)
{
	int	i;
	char *tmp;
	char **tmp3;

	i = 0;
	while (data.args && data.args[i])
	{
		tmp = data.args[i];
		data.args[i] = ft_strtrim(data.args[i], " \t\n\r\v\f");
		free(tmp);
		tmp3 = ft_split_l(data.args[i], " ");
		ft_print_dchar(tmp3);
		tmp = data.args[i];
		data.args[i] = ft_join(tmp3);
		fprintf(stderr, "STR2, vaut %s\n", data.args[i]);
		free(tmp);
		fprintf(stderr, "P DE TMP# vaut %p et ARGS vaut %p\n", tmp3 ,data.args);
		// ft_free_dchar(tmp3);
		i++;
	}
	fprintf(stderr, "HEEEEEEY %s \n", data.args[0]);
	ft_print_args();
	return (0);
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

char	*ft_clean2(char *str)
{
	int	i;
	char *tmp;
	int	in_q;

	i = 0;
	in_q = 0;
	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (free(str), exit(-1), NULL);
	free(tmp);
	fprintf(stderr, "trim vaut |%s|\n", str);
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
	// (void)str;
	str = ft_clean2(str);
	// data.args = ft_split_k(str, data.sep);
	// if (!data.args)
	// 	  return (1);
	// ft_clean();
	fprintf(stderr, "STRING VAUT |%s|\n", str);
	// ft_print_args();
	//  return(ft_detect());
	 return (str);
}

// int ft_detect_cmd(void)
// {
// 	int  count_w;

// 	count_w = 0;
// 	ft_split_mini();

// 	return (0);
// }