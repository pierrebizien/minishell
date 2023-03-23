#include "../_Include/minishell.h"

extern int g_err_value;

char *ft_parse(char *str, t_data *data) // CHECK GLOBAL ET SI > >OUT RETURN ERROR
{
	char *tmp;

	str = ft_convert_variable(str, data);
	tmp = str;
	str = ft_strtrim(str, WS);
	if (!str)
		return (ft_pb_malloc(data), free(tmp), NULL);
	free(tmp);
	str = ft_clean(str, data);
	if (!str || ft_verif_et_ou(str) == 0 || ft_verif_just_chev(str) == 0 || ft_verif_pipe(str) == 0)
	{
		free(str);
		ft_free_env(data);
		free(data->pwd);
		free(data->oldpwd);
		g_err_value = 2;
		return (NULL);
	}
	data->args = ft_split_k(str, "|");
	if (data->args == NULL)
		return (ft_pb_malloc(data), free(str), NULL);
	ft_clean_ws(data);
	 return (str);
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
			return (ft_pb_malloc(data), -42);
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
				else if (0 < i && tab[i-1] && ft_strlen(tab[i - 1]) != 0 && !ft_strncmp(tab[i - 1], "<<" , ft_strlen(tab[i - 1])))
				{
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
		if (g_err_value == MAL_ERCODE)
			return(ft_free_list(&data->exec), fprintf(stderr, "ERROR 17\n"), ft_pb_malloc(data), g_err_value);
		return (g_err_value);
	}
	data->pip.nb_pipes = ft_count_pipes(&data->exec);
	return (0);
}
