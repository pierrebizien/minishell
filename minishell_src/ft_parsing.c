#include "./inc/minishell.h"

extern t_data data;

// void ft_print_dchar(char **strstr)
// {
// 	int	i;

// 	i = 0;
// 	while (strstr && strstr[i])
// 	{
// 		printf("STRSTR VAUT |%s|\n", strstr[i]);
// 		i++;
// 	}
	
// }


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
	int	in_dq;
	int	in_sq;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (str && str[i])
	{
		if (str[i] == '"')
		{
			in_dq = ft_in_q(in_dq);
		}
		else if (str[i] == '\'')
		{
			in_sq = ft_in_q(in_sq);
		}
		if (!in_dq && !in_sq && is_ws(str[i]) && is_ws(str[i + 1]))
			ft_memmove(str + i, (str + i + 1), ft_strlen(str + i) + 2);
		else if ((str[i] == '<' && str[i+1] != '<' && str[i+1] != ' ') || (str[i] == '>' && str[i+1] != '>' && str[i+1] != ' '))
		{
			
		}
		else
			i++;
	}
	if (in_dq || in_sq)
		return (free(str), write(2, "Quotes error\n", 14), NULL);
	return (str);
}
void	ft_clean_ws(t_data *data)
{
	int	i;
	int k;

	i = 0;
	while (data->args && data->args[i])
	{

		if (is_ws(data->args[i][0]))
			ft_memmove(data->args[i], data->args[i] + 1, ft_strlen(data->args[i]));
		k = ft_strlen(data->args[i]);
		if (is_ws(data->args[i][k - 1]))
			data->args[i][k - 1] = '\0';
		i++;
	}
	
}


char *ft_parse(char *str, t_data *data)
{
	char *tmp;

	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (free(str), exit(-1), NULL);
	free(tmp);
	str = ft_clean(str);
	if (!str)
		return (NULL);
	data->args = ft_split_k(str, "|");
	ft_clean_ws(data);
	// ft_print_args();
	// printf("str parse vaut |%s|\n", str);
	 return (str);
}


t_exec	*ft_lstnew_pars(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (new == NULL)
		return (NULL);
	new->str = NULL;
	new->id = -42;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void ft_parse_for_exec(t_data *data)
{
	int i;
	int j;
	t_exec *tmp;
	char **tab;


	tmp = &data->exec;
	tmp->prev = NULL;
	i = 0;
	j = -1;
	while (data->args[++j])
	{
		tmp->next = ft_lstnew_pars();

		tab = ft_split_l(data->args[j], " ");
		ft_print_dchar(tab);


		// i = ft_strlen(data.args[j]);
		
	}
}


// < Makefile <<stop ls a > out -la b c