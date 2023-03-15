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
		if (str[i] == '"' && !in_sq)
		{
			in_dq = ft_in_q(in_dq);
		}
		else if (str[i] == '\'' && !in_dq)
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

static void	ft_maj_quotes(int *dq, int *sq, char c)
{
	if (c == '"' && *sq == -1)
		*dq *= -1;
	if (c == '\'' && *dq == -1)
		*sq *= -1;
}

size_t	ft_strlen_var_env(char *str)
{
	int	i;

	i = 1;
	if (str && ft_isdigit(str[1]))
		return (2);
	while (str && str[i])
	{
		// fprintf(stderr, "\t\tstrlen[%d]= %s(%c)(%d)\n\n", i, str + i, str[i], str[i]);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}
size_t	ft_strlen_WS_quotes(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (is_ws(str[i]) == 0 && str[i] != '"' && str[i] != '\''))
		i++;
	return (i);
}

char	*ft_check_env(char *str, t_data *data)
{
	t_env *tmp_env;
	tmp_env = &data->env;
	if (str && str[0]=='?')
		return (ft_itoa(data->last_err_num));
	while (tmp_env)
	{
		if (!strncmp(str, tmp_env->key, ft_strlen_var_env(str)))
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
	
}

int	ft_is_hd(char *str, int	i)
{
	int	j;

	j = 0;
	if (i > 0)
		i--;
	else
		return (0);
	while (str && i >= 0 && is_ws(str[i]))
		i--;
	if (i > 0 && str[i] == '<'  && str[i - 1] == '<')
		return (1);
	return (0);
}
char *ft_convert_variable(char *str, t_data *data)
{
	int	i;
	int dq;
	int sq;
	char *var;
	// int test_a_sup;
	
	sq = -1;
	dq = -1;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ft_maj_quotes(&dq, &sq, str[i]);
		if (str[i] == '$' && str[i + 1] && !is_ws(str[i + 1]) && sq == -1)
		{
			var = ft_check_env(str + i + 1, data);
			// if (!var && ft_is_hd(str, i))
			if (var && '0' <= var[0] && var[0] <= '9')
			{
				ft_memmove(str + i, str + i + 2, ft_strlen(str + i));
				str = ft_put_str_in_str(str, var, i);
				i = 0;
			}
			else if (!var && !ft_is_hd(str, i))
			{

				ft_memmove(str + i, str + i + ft_strlen_var_env(str + i), ft_strlen(str + i + ft_strlen_var_env(str + i))+ 1);
				str = ft_put_str_in_str(str, var, i);
				i = 0;
			}
		}
		i++;
	}
	return (str);
	
	//PENSER A FREE
}

char *ft_convert_variable_hd(char *str, t_data *data, char *delimiter)
{
	int	i;
	int dq;
	int sq;
	char *var;
	// int test_a_sup;
	
	sq = -1;
	dq = -1;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			ft_maj_quotes(&dq, &sq, str[i]);
		if (str[i] == '$' && str[i + 1] && !is_ws(str[i + 1]) && sq == -1)
		{
			var = ft_check_env(str + i + 1, data);
			// if (!var && ft_is_hd(str, i))
			if (var && '0' <= var[0] && var[0] <= '9')
			{
				ft_memmove(str + i, str + i  + 2, ft_strlen(str + i));
				str = ft_put_str_in_str(str, var, i);
				i = 0;
			}
			else if (!var && ft_strncmp(delimiter, str, ft_strlen(str + i)))
			{
				ft_memmove(str + i, str + i  + ft_strlen_var_env(str + i), ft_strlen(str + i + ft_strlen_var_env(str + i))+ 1);
				str = ft_put_str_in_str(str, var, i);
				i = 0;
			}
		}
		i++;
	}
	return (str);
}

char *ft_parse(char *str, t_data *data) // CHECK GLOBAL ET SI > >OUT RETURN ERROR
{
	char *tmp;

	tmp = str;
	str = ft_convert_variable(str, data);
	str = ft_strtrim(str, WS);
	if (!str || str[0] == '\0')
		return (free(str), NULL);
	str = ft_clean(str);
	if (!str)
		return (NULL);
	data->args = ft_split_k(str, "|");
	// fprintf(stderr, "\n\nApres split pipe vaut :\n");
	ft_clean_ws(data);
	// ft_print_dchar(data->args);
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
	new->hd_filename = NULL;
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
	// free(tmp->next);
	tmp->next = NULL;
}
int	ft_find_if_hd_quotes(t_data *data, int count_p)
{
	// int count;
	t_exec *tmp;
	int len1;
	int len2;

	tmp = &data->exec;
	// count = 0;
	(void)count_p;
	len1 = ft_strlen(data->args[count_p]);
	len2 = len1;
	while (len1 - 1)
	{
		if (len1 - 2 >= 0 && data->args[count_p][len1 - 1] == '<' && data->args[count_p][len1 - 2] == '<')
		{
			if (len1 != len2 && (data->args[count_p][len2 - 1] == '\'' || data->args[count_p][len2 - 1] == '"'))
				return (1);
		}
		len1--;

	}
	return (0);
}


void ft_modif_in_out(t_data *data)
{
	t_exec	*tmp;
	int		bool_out;
	int		bool_in;
	int count_p;
	t_exec	*tmpstart;

	count_p = 0;
	tmp = &data->exec;

	while (tmp != NULL)
	{
		tmpstart = tmp;
		bool_in = 0;
		bool_out = 0;
		while (tmp->next != NULL && tmp->id != F_PIPE)
			tmp = tmp->next;
		if (tmp->id == F_PIPE)
			tmp = tmp->prev;
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
			if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ)
			{
				if (bool_in == 1)
				{
					ft_init_sigint_hd();
					ft_heredoc(data, tmp->str, 0, 0);
					ft_init_sigint();
					tmp->id = F_FALSED;
				}
				else if (tmp->id == F_DELIMITER)
				{
					ft_init_sigint_hd();
					tmp->hd_filename = ft_heredoc(data, tmp->str, 1, 0);
					ft_init_sigint();
					bool_in = 1;
				}
				else 
				{
					ft_init_sigint_hd();
					tmp->hd_filename = ft_heredoc(data, tmp->str, 1, 1);
					ft_init_sigint();
					bool_in = 1;
				}
			}
			tmp = tmp->prev;
		}
		tmp = tmpstart;
		if (tmp->id == F_PIPE && tmp->next != NULL)
			tmp = tmp->next;
		while (tmp->next != NULL && tmp->id != F_PIPE)
			tmp = tmp->next;
		if (tmp != NULL)
		{
			tmp = tmp->next;
			// count_p ++;
		}
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
	int count_p;
	t_exec *tmp;
	char **tab;


	tmp = &data->exec;
	j = -1;
	count_p = 0;
	while (data->args[++j])
	{
		tab = ft_split_lq(data->args[j], " ");
		i = 0;
		while (tab && tab[i])
		{
			
			tab[i] = ft_strtrim(tab[i], "\"'");
			if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], "<", ft_strlen(tab[i])))
				i++;
			else if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], "<<", ft_strlen(tab[i])))
				i++;
			else if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], ">", ft_strlen(tab[i])))
				i++;
			else if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], ">>", ft_strlen(tab[i])))
				i++;
			else if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], "|", ft_strlen(tab[i])))
			{
				count_p++;
				tmp->id = F_PIPE;
				tmp->str = ft_strdup(tab[i]);
				tmp->next = ft_lstnew_pars();
				tmp = tmp->next;
				i++;
			}
			else
			{
				fprintf(stderr, "au else i = %d\n", i);
				if (ft_strlen(tab[i - 1]) != 0 && 0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], "<", ft_strlen(tab[i - 1])))
				{
					fprintf(stderr, "1\ti = %d\n", i);
					tmp->id = F_INFILE;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else if (ft_strlen(tab[i - 1]) != 0 && 0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], "<<", ft_strlen(tab[i - 1])))
				{
					fprintf(stderr, "2\ti = %d\n", i);
					if (ft_find_if_hd_quotes(data, count_p))
						tmp->id = F_DELIMITER_SQ;
					else
						tmp->id = F_DELIMITER;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else if (ft_strlen(tab[i - 1]) != 0 && 0 < i && tab[i - 1] && !ft_strncmp(tab[i - 1], ">", ft_strlen(tab[i - 1])))
				{
					fprintf(stderr, "3\ti = %d\n", i);
					tmp->id = F_TRONC;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else if (ft_strlen(tab[i - 1]) != 0 && 0 < i && tab[i-1] && !ft_strncmp(tab[i - 1], ">>", ft_strlen(tab[i - 1])))
				{
					fprintf(stderr, "4\ti = %d\n", i);
					tmp->id = F_APPEND;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
				else
				{
					fprintf(stderr, "5\ti = %d\n", i);
					tmp->id = F_CMD;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					tmp = tmp->next;
					i++;	
				}
			}
		}
	}
	ft_clean_list_exec(data);
	ft_modif_in_out(data);
	ft_print_list(&data->exec);
	data->pip.nb_pipes = ft_count_pipes(&data->exec);
}


// < Makefile <<stop ls a > out -la b c | cat | ls -la >out >> out2

// < make <<test <oui << stop cat > out -ls >sexe >>bisous

// < make <<test <oui << stop cat > out -ls >sexe >>bisous | < infule << stop <out ls od > test >> out -la > out 