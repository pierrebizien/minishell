#include "../_Include/minishell.h"

extern int err_value;

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
void	ft_print_list(t_exec *begin)
{
	while (begin)
	{
		fprintf(stderr, "(%d) \t |%s|\n", begin->id, begin->str);
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

char	*ft_clean(char *str, t_data *data)
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
		// fprintf(stderr, "entree boucle str + i %s\n", str + i);
		if (str[i] == '"' && !in_sq)
		{
			if (i <= 0 || str[i - 1] != '\\')
				in_dq = ft_in_q(in_dq);
		}
		else if (str[i] == '\'' && !in_dq)
		{
			in_sq = ft_in_q(in_sq);
		}
		if (!in_dq && !in_sq && is_ws(str[i]) && is_ws(str[i + 1]))
			ft_memmove(str + i, (str + i + 1), ft_strlen(str + i + 1) + 1);
		else if (in_sq == 0 && in_dq == 0 && ((str[i] && str[i] == '<' && str[i+1] != '<' && str[i+1] != ' ' && str[i+1]) || (str[i] == '>' && str[i+1] != '>' && str[i+1] != ' ' && str[i+1])))
		{
			// fprintf(stderr, "on rentre 1 str + i vaut %s et dq vaut %d\n", str + i, in_dq);
			tmp = ft_put_str_in_str(str, " ", ++i);
			if (!tmp)
				return (free(str), fprintf(stderr, "ERROR 5\n"), ft_pb_malloc(data), NULL);
			free(str);
			str = tmp;
		}
		else if (in_sq == 0 && in_dq == 0 && ((str[i] && str[i] != '<' && str[i] != ' ' && str[i + 1] && str[i + 1] == '<') || (str[i] && str[i] != '>' && str[i] != ' ' && str[i + 1] && str[i + 1] == '>')))
		{
			// fprintf(stderr, "on rentre 2 str + i vaut %s et dq vaut %d\n", str + i, in_dq);
			tmp = ft_put_str_in_str(str, " ", ++i);
			if (!tmp)
				return (free(str), fprintf(stderr, "ERROR 6\n"), ft_pb_malloc(data), NULL);
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

void	ft_maj_quotes(int *dq, int *sq, char c)
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
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
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
		return (ft_itoa(err_value));
	while (tmp_env)
	{
		if (!strncmp(str, tmp_env->key, ft_strlen_var_env(str)))
			return (ft_strdup(tmp_env->value));
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
	while (str && i >= 0 && (is_ws(str[i]) || str[i] == '"' || str[i] == '\''))
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
	char *tmp;
	// int test_a_sup;
	
	sq = -1;
	dq = -1;
	i = 0;
	while (str && str[i])
	{
		// fprintf(stderr, "dans convert str vaut %s\n", str + i);
		if (str[i] == '\'' || str[i] == '"')
				ft_maj_quotes(&dq, &sq, str[i]);
		if ((sq == 1 || dq == 1) && str[i] == '$' && (str[i + 1] == '"' || is_ws(str[i + 1]) ||  str[i + 1] == '\''))
			i++;
		if (str[i] && str[i] == '$' && str[i + 1] && !is_ws(str[i + 1]) && sq == -1)
		{
			var = ft_check_env(str + i + 1, data);
			if (!ft_is_hd(str, i))
			{
				// fprintf(stderr, "ft_strlen_var_env(str + i) = %zu\n", ft_strlen_var_env(str + i));
				ft_memmove(str + i, str + i + ft_strlen_var_env(str + i), ft_strlen(str + i + ft_strlen_var_env(str + i))+ 1);
				tmp = str;
				str = ft_put_str_in_str(str, var, i);
				if (!str)
					return (free(var), free(tmp), NULL);
				free(tmp);
			}
			else
				i++;
			free(var);
		}
		else
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
	char *tmp;
	// int test_a_sup;
	
	sq = -1;
	dq = -1;
	i = 0;
	while (str && str[i])
	{
		if ((str[i] == '\'' || str[i] == '"'))
				ft_maj_quotes(&dq, &sq, str[i]);
		if (str[i] == '$' && str[i + 1] && !is_ws(str[i + 1]) && sq == -1)
		{
			var = ft_check_env(str + i + 1, data);
			if (ft_strncmp(delimiter, str, ft_strlen(str)))
			{
				ft_memmove(str + i, str + i + ft_strlen_var_env(str + i), ft_strlen(str + i + ft_strlen_var_env(str + i))+ 1);
				tmp = str;
				str = ft_put_str_in_str(str, var, i);
				if (!str)
				{
					err_value = MAL_ERCODE;
					return (free(var), free(tmp), NULL);
				}
				free(tmp);
			}
			free(var);
		}
		if (str && str[i])
			i++;
	}
	return (str);
}


int ft_verif_et_ou(char *str)
{
	int i;
	int dq;
	int sq;

	i = 0;
	dq = -1;
	sq = -1;
	while (str && str[i])
	{
		ft_maj_quotes(&dq, &sq, str[i]);
		if (dq != 1 && sq != 1 && str[i] == '&')
			return (ft_putstr_fd("error: unexpected `&'\n", 2), 0);
		if (dq != 1 && sq != 1 && str[i] == ';')
			return (ft_putstr_fd("error: unexpected `;'\n", 2), 0);
		else if (dq != 1 && sq != 1 && str[i] == '|' && str[i+1] == '|')
			return (ft_putstr_fd("error: unexpected `||'\n", 2), 0);
		else
			i++;
	}
	return (1);
}

void	ft_pb_malloc(t_data *data)
{
	ft_free_env(data);
	free(data->oldpwd);
	free(data->pwd);
	ft_putstr_fd("MALLOC ERRRRROR\n", 2);
	exit(MAL_ERCODE);

}

int ft_verif_pipe(char *str)
{
	int i;
	int j;
	int dq;
	int sq;

	i = 0;
	dq = -1;
	sq = -1;
	while (str && str[i])
	{
		ft_maj_quotes(&dq, &sq, str[i]);
		if (dq != 1 && sq != 1 && str[i] == '|')
		{
			j = i - 1;
			while (0 <= j && is_ws(str[j]) == 1)
				j--;
			if (j == -1)
				return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), 0);
			j = i + 1;
			while (1)
			{
				if (is_ws(str[j]))
					j++;
				else if (str[j] == '\0')
					return (ft_putstr_fd("syntax error near unexpected token `newline'\n", 2), 0);
				else
					break ;
			}
		}
		i++;
	}
	return (1);
}


int ft_verif_just_chev(char *str)
{
	int i;
	int j;
	int dq;
	int sq;

	i = 0;
	dq = -1;
	sq = -1;
	while (str && str[i])
	{
		ft_maj_quotes(&dq, &sq, str[i]);
		if (dq != 1 && sq != 1 && ((str[i] == '<' && str[i+1] != '<') || (str[i] == '>' && str[i+1] != '>')))
		{
			j = i + 1;
			while (1)
			{
				if (is_ws(str[j]))
					j++;
				else if (str[j] == '<' || str[j] == '>' || str[j] == '|')
					return (ft_putstr_fd("syntax error near unexpected token `", 2), ft_putchar_fd(str[j], 2), ft_putstr_fd("'\n", 2), 0);
				else if (str[j] == '\0')
					return (ft_putstr_fd("syntax error near unexpected token `newline'\n", 2), 0);
				else
					break ;
			}
		}
		i++;
	}
	return (1);
}


char *ft_parse(char *str, t_data *data) // CHECK GLOBAL ET SI > >OUT RETURN ERROR
{
	char *tmp;

	str = ft_convert_variable(str, data);
	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (fprintf(stderr, "ERROR 7\n"), ft_pb_malloc(data), free(tmp), NULL);
	free(tmp);
	str = ft_clean(str, data);
	if (!str || ft_verif_et_ou(str) == 0 || ft_verif_just_chev(str) == 0 || ft_verif_pipe(str) == 0)
	{
		fprintf(stderr, "\n\n\n\n\nFREEEEEE\n\n\n\n\n\n\n\n");
		free(str);
		ft_free_env(data);
		free(data->pwd);
		free(data->oldpwd);
		err_value = 2;
		return (NULL);
	}

	data->args = ft_split_k(str, "|");
	if (data->args == NULL)
		return (fprintf(stderr, "ERROR 8\n"), ft_pb_malloc(data), free(str), NULL);
	ft_clean_ws(data);
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

char	*ft_clean_quotes(char *str)
{
	int	i;
	int sq;
	int dq;

	i = 0;
	sq = -1;
	dq = -1;
	while (str && str[i])
	{
		if ((str[i] == '"' && sq == -1) || (str[i] == '\'' && dq == -1))
		{
				ft_maj_quotes(&dq, &sq, str[i]);
				ft_memmove(str + i, str + i + 1, ft_strlen(str + i + 1) + 1);
		}
		else 
			i++;
	}
	return (str);
	
}

void ft_clean_list_exec(t_data *data)
{
	t_exec *tmp;
	t_exec *before;


	tmp = &data->exec;
	tmp->prev = NULL;
	while (tmp->next != NULL)
	{
		
		tmp->quotes = malloc(sizeof(char) * 2);
		if (!tmp->quotes)
			return (ft_free_end(data), fprintf(stderr, "ERROR 9\n"), ft_pb_malloc(data));
		tmp->quotes[0] = '0';
		tmp->quotes[1] = '\0';
		if (tmp->str[0] == '\'' || tmp->str[0] == '"')
			tmp->quotes[0] = '1';
		tmp->str = ft_clean_quotes(tmp->str);

		before = tmp;
		tmp = tmp->next;
		if (tmp != NULL)
			tmp->prev = before;
	}
	tmp = tmp->prev;
	free(tmp->next);
	tmp->next = NULL;
}

char ft_first_no_chev(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != '<' && !is_ws(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
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
			if (len1 != len2 && (ft_first_no_chev(data->args[count_p] + len1) == '\'' || ft_first_no_chev(data->args[count_p] + len1) == '"'))
				return (1);
		}
		len1--;

	}
	return (0);
}


int ft_modif_in_out(t_data *data)
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
					tmp->id = F_FALSED;
				else
					bool_in = 1;
			}
			tmp = tmp->prev;
		}
		tmp = tmpstart;
		if (tmp->id == F_PIPE && tmp->next != NULL)
			tmp = tmp->next;
		while (tmp != NULL && tmp->id != F_PIPE)
		{
			if (tmp->id == F_DELIMITER || tmp->id == F_DELIMITER_SQ || tmp->id == F_FALSED)
			{
				if (tmp->id == F_FALSED)
				{
					ft_init_sigint_hd();
					ft_heredoc(data, tmp->str, 0, 0);
					if (err_value == 130)
						return (ft_free_list(&data->exec), 1);
					if (err_value == MAL_ERCODE)
						return (MAL_ERCODE);
					ft_init_sigint();
				}
				else if (tmp->id == F_DELIMITER)
				{
					ft_init_sigint_hd();
					tmp->hd_filename = ft_heredoc(data, tmp->str, 1, 0);
					if (err_value == 130)
						return (ft_free_list(&data->exec), 1);
					if (err_value == MAL_ERCODE)
						return (MAL_ERCODE);
					ft_init_sigint();
				}
				else 
				{
					ft_init_sigint_hd();
					tmp->hd_filename = ft_heredoc(data, tmp->str, 1, 1);
					if (err_value == 130)
						return (ft_free_list(&data->exec), 1);
					if (err_value == MAL_ERCODE)
						return (MAL_ERCODE);
					ft_init_sigint();
				}
			}
			tmp = tmp->next;
		}
		if (tmp != NULL)
		{
			tmp = tmp->next;
			// count_p ++;
		}
		// fprintf(stderr, "en bas(%d) \t %s\t next = %p\n", tmp->id, tmp->str,tmp->next);

	}
		// ft_print_list(&data->exec);
		return (0);
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
int ft_check_chev_pip(char **tab)
{
	int	i;

	i = 0;
	while(tab && tab[i])
	{
		if (ft_strlen(tab[i]) != 0 && !ft_strncmp(tab[i], "<", ft_strlen(tab[i])))
			if (tab[i + 1] && ft_strlen(tab[i + 1]) != 0 && !ft_strncmp(tab[i + 1], "<", ft_strlen(tab[i + 1])))
				return (1);
		i++;
	}
	return (0);
	
}

int	ft_check_if_past_is_delim(t_exec *begin, int i)
{
	t_exec *tmp;
	int	j;

	j = 0;
	(void)i;
	tmp = begin;
	while (tmp && tmp->next && tmp->next->next)
	{
		tmp = tmp->next;
		j++;
	}
	if (tmp && (tmp->id == 4 || tmp->id == 1))
		return (1);
	else
		return (0);
	return (0);

}

int ft_parse_for_exec(t_data *data)
{
	int i;
	int j;
	int count_p;
	t_exec *tmp;
	char **tab;


	free(data->to_free.str);
	tmp = &data->exec;
	tmp->id = -43;
	tmp->next = NULL;
	tmp->hd_filename = NULL;
	tmp->str = NULL;
	j = -1;
	count_p = 0;
	while (data->args[++j])
	{
		tab = ft_split_lq(data->args[j], " ");
		if (tab == NULL)
			return (fprintf(stderr, "ERROR 10\n"), ft_pb_malloc(data), -42);
		// ft_print_dchar(tab);
		if (ft_check_chev_pip(tab) == 1)
			return (1);
		i = 0;
		while (tab && tab[i])
		{
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
				tmp->hd_filename = NULL;
				tmp->str = ft_strdup(tab[i]);
				tmp->next = ft_lstnew_pars();
				if (!tmp->str || !tmp->next)
					return (ft_free_list(&data->exec), ft_free_dchar(tab), fprintf(stderr, "ERROR 11\n"), ft_pb_malloc(data), -42);
				tmp = tmp->next;
				tmp->next = NULL;
				i++;
			}
			else
			{
				// tab[i] = ft_strtrim(tab[i], "\"'");
				if (0 < i && tab[i-1] && ft_strlen(tab[i - 1]) != 0 && !ft_strncmp(tab[i - 1], "<", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_INFILE;
					tmp->hd_filename = NULL;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					if (!tmp->str || !tmp->next)
						return (ft_free_list(&data->exec), ft_free_dchar(tab), fprintf(stderr, "ERROR 12\n"), ft_pb_malloc(data), -42);
					tmp = tmp->next;
					tmp->next = NULL;
					i++;	
				}
				else if (0 < i && tab[i-1] /* && ft_check_if_past_is_delim(&data->exec, i) == 0 */&& ft_strlen(tab[i - 1]) != 0 && !ft_strncmp(tab[i - 1], "<<" , ft_strlen(tab[i - 1])))
				{
					// if (tab[i][0] == 'c')
					if (ft_find_if_hd_quotes(data, count_p))
						tmp->id = F_DELIMITER_SQ;
					else
						tmp->id = F_DELIMITER;
					tmp->hd_filename = NULL;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					if (!tmp->str || !tmp->next)
						return (ft_free_list(&data->exec), ft_free_dchar(tab), fprintf(stderr, "ERROR 13\n"), ft_pb_malloc(data), -42);
					tmp = tmp->next;
					tmp->next = NULL;
					i++;	
				}
				else if (0 < i && tab[i-1] && ft_strlen(tab[i - 1]) != 0 && !ft_strncmp(tab[i - 1], ">", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_TRONC;
					tmp->hd_filename = NULL;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					if (!tmp->str || !tmp->next)
						return (ft_free_list(&data->exec), ft_free_dchar(tab), fprintf(stderr, "ERROR 14\n"), ft_pb_malloc(data), -42);
					tmp = tmp->next;
					tmp->next = NULL;
					i++;	
				}
				else if (0 < i && tab[i-1] && ft_strlen(tab[i - 1]) != 0 && !ft_strncmp(tab[i - 1], ">>", ft_strlen(tab[i - 1])))
				{
					tmp->id = F_APPEND;
					tmp->hd_filename = NULL;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					if (!tmp->str || !tmp->next)
						return (ft_free_list(&data->exec), ft_free_dchar(tab),fprintf(stderr, "ERROR 15\n"),  ft_pb_malloc(data), -42);
					tmp = tmp->next;
					tmp->next = NULL;
					i++;	
				}
				else
				{
					tmp->id = F_CMD;
					tmp->str = ft_strdup(tab[i]);
					tmp->next = ft_lstnew_pars();
					if (!tmp->str || !tmp->next)
						return (ft_free_list(&data->exec), ft_free_dchar(tab), fprintf(stderr, "ERROR 16\n"), ft_pb_malloc(data), -42);
					tmp->hd_filename = NULL;
					tmp = tmp->next;
					tmp->next = NULL;
					i++;	
				}
			}
		}
		ft_free_dchar(tab);
	}
	ft_free_dchar(data->args);
	ft_clean_list_exec(data);
	if (ft_modif_in_out(data))
	{
		if (err_value == MAL_ERCODE)
			return(ft_free_list(&data->exec), fprintf(stderr, "ERROR 17\n"), ft_pb_malloc(data), err_value);
		return (err_value);
	}
	data->pip.nb_pipes = ft_count_pipes(&data->exec);
	return (0);
}


// < Makefile <<stop ls a > out -la b c | cat | ls -la >out >> out2

// < make <<test <oui << stop cat > out -ls >sexe >>bisous

// < make <<test <oui << stop cat > out -ls >sexe >>bisous | < infule << stop <out ls od > test >> out -la > out 


// ./
// ./: Is a directory
// ==292593== 
// ==292593== HEAP SUMMARY:
// ==292593==     in use at exit: 208,337 bytes in 225 blocks
// ==292593==   total heap usage: 771 allocs, 546 frees, 252,589 bytes allocated
// ==292593== 
// ==292593== LEAK SUMMARY:
// ==292593==    definitely lost: 0 bytes in 0 blocks
// ==292593==    indirectly lost: 0 bytes in 0 blocks
// ==292593==      possibly lost: 0 bytes in 0 blocks
// ==292593==    still reachable: 0 bytes in 0 blocks
// ==292593==         suppressed: 208,337 bytes in 225 blocks
// ==292593== 
// ==292593== For lists of detected and suppressed errors, rerun with: -s
// ==292593== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
// minishell (/minishell) ls | ls -la < Makefile >out |  
// syntax error near unexpected token `newline'
// minishell (/minishell) 
// minishell (/minishell) ls | ls -la < Makefile >out
// minishell (/minishell) ls | ls -la < Makefile >out | env