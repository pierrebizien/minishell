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
void	ft_print_list(t_exec *begin)
{
	while (begin)
	{
		fprintf(stderr, "(%d) \t %s\n", begin->id, begin->str);
		begin = begin->next;
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
	int	in_dq;
	int	in_sq;
	char *tmp;

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
		else if ((str[i] == '<' && str[i+1] != '<' && str[i+1] != ' ' && str[i+1]) || (str[i] == '>' && str[i+1] != '>' && str[i+1] != ' ' && str[i+1]))
		{
			tmp = ft_put_str_in_str(str, " ", ++i);
			free(str);
			str = tmp;
		}
		else if ((str[i] && str[i] != '<' && str[i] != ' ' && str[i + 1] && str[i + 1] == '<') || (str[i] && str[i] != '>' && str[i] != ' ' && str[i + 1] && str[i + 1] == '>'))
		{
			tmp = ft_put_str_in_str(str, " ", ++i);
			free(str);
			str = tmp;
			i++;
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


char *ft_parse(char *str, t_data *data) // CHECK GLOBAL ET SI > >OUT RETURN ERROR
{
	char *tmp;

	tmp = str;
	str = ft_strtrim(str, WS);
	// printf("str parse vaut |%s|\n", str);
	if (!str || str[0] == '\0')
		return (free(str), NULL);
	// free(tmp);
	str = ft_clean(str);
	if (!str)
		return (NULL);
	data->args = ft_split_k(str, "|");
	ft_clean_ws(data);
	// ft_print_args();
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

void ft_clean_list_exec(t_data *data)
{
	t_exec *tmp;
	t_exec *before;


    tmp = &data->exec;
	tmp->prev = NULL;
	while (tmp->next != NULL)
    {
        before = tmp;
		tmp = tmp->next;
		if (tmp != NULL)
			tmp->prev = before;
	}
	tmp = tmp->prev;
	free(tmp->next);
	tmp->next = NULL;
}

void ft_modif_in_out(t_data *data)
{
	t_exec	*tmp;
	int		bool_out;
	int		bool_in;
	t_exec	*tmpstart;

	tmp = &data->exec;
	while (tmp->next != NULL)
	{
		tmpstart = tmp;
		// fprintf(stderr, "chiasse(%d) \t %s\t cul = %d\n", tmp->id, tmp->str, bool_out);
		bool_in = 0;
		bool_out = 0;
		while (tmp->next != NULL && tmp->id != F_PIPE)
			tmp = tmp->next;
		if (tmp->id == F_PIPE)
			tmp = tmp->prev;
		// fprintf(stderr, "nico(%d) \t %s\t cul = %d\n", tmp->id, tmp->str, bool_out);
		while (tmp != NULL && tmp->id != F_PIPE)
		{
			if (tmp->id == F_APPEND)
			{
				if (bool_out == 1)
					tmp->id = F_FALSEA;
				else
					bool_out = 1;
			}
			if (tmp->id == F_TRONC)
			{
				if (bool_out == 1)
					tmp->id = F_FALSET;
				else
					bool_out = 1;
			}
			if (tmp->id == F_INFILE)
			{
				if (bool_in == 1)
					tmp->id = F_FALSEI;
				else
					bool_in = 1;
			}
			if (tmp->id == F_DELIMITER)
			{
				if (bool_in == 1)
					tmp->id = F_FALSED;
				else
					bool_in = 1;
			}
			// fprintf(stderr, "cacaa(%d) \t %s\t culin = %d\t cutout = %d\n", tmp->id, tmp->str,bool_in,  bool_out);
			tmp = tmp->prev;
		}
		tmp = tmpstart;
		if (tmp->id == F_PIPE && tmp->next != NULL)
			tmp = tmp->next;
		while (tmp->next != NULL && tmp->id != F_PIPE)
			tmp = tmp->next;
		if (tmp->next != NULL)
			tmp = tmp->next;
		// fprintf(stderr, "en bas(%d) \t %s\t next = %p\n", tmp->id, tmp->str,tmp->next);
		

	}
}
int	ft_count_pipes (t_exec *begin)
{
	int count;
	t_exec *tmp;

	tmp = begin;
	count = 0;
	while (begin)
	{
		if (begin->id == F_PIPE)
			count++;
		begin = begin->next;
	}
	return (count);
	
}

void ft_parse_for_exec(t_data *data)
{
	int i;
	int j;
	t_exec *tmp;
	char **tab;


	tmp = &data->exec;
	j = -1;
	while (data->args[++j])
	{
		tab = ft_split_l(data->args[j], " ");
		i = 0;
		while (tab && tab[i])
		{

			if (!ft_strncmp(tab[i], "<", ft_strlen(tab[i])))
				i++;
			else if (!ft_strncmp(tab[i], "<<", ft_strlen(tab[i])))
				i++;
			else if (!ft_strncmp(tab[i], ">", ft_strlen(tab[i])))
				i++;
			else if (!ft_strncmp(tab[i], ">>", ft_strlen(tab[i])))
				i++;
			else if (!ft_strncmp(tab[i], "|", ft_strlen(tab[i])))
			{
				tmp->id = F_PIPE;
				tmp->str = ft_strdup(tab[i]);
				tmp->next = ft_lstnew_pars();
				tmp = tmp->next;
				i++;
			}
			else
			{
				if (0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], "<", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_INFILE;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else if (0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], "<<", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_DELIMITER;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else if (0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], ">", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_TRONC;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else if (0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], ">>", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_APPEND;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else
				{
					tmp->id = F_CMD;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
			}
		}
		ft_free_dchar(tab);
	}
	ft_clean_list_exec(data);
	ft_modif_in_out(data);
	// ft_print_list(&data->exec);
	data->pip.nb_pipes = ft_count_pipes(&data->exec);

	// exit(1);
		
}


// < Makefile <<stop ls a > out -la b c | cat | ls -la >out >> out2

// < make <<test <oui << stop cat > out -ls >sexe >>bisous

// < make <<test <oui << stop cat > out -ls >sexe >>bisous | < infule << stop <out ls od > test >> out -la > out 