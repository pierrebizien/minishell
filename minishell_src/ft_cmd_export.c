#include "./inc/minishell.h"

size_t	ft_strlen_WS(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_ws(str[i]) == 0)
		i++;
	return (i);
}

static int ft_just_export(t_data *data)
{
	t_env *tmp;

    tmp = &data->env;
    while (tmp)
    {
		write(1, "export ", 8);
        write(1, tmp->key, ft_strlen(tmp->key));
        write(1, "=", 1);
        write(1, tmp->value, ft_strlen(tmp->value));
        write(1, "\n", 1);
        tmp = tmp->next;
    }
	return (0);
}

static void ft_export_var_in_env(char *str, int i, t_data *data)
{
    t_env	*tmp;
	tmp = &data->env;
	if (str[i] == 0)
		i++;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, str, i) == 0)
			tmp->printable = 1;
		tmp = tmp->next;
	}
}


static int ft_plus_egal_export(char *str, t_data *data)
{
    t_env	*tmp;
	char	*var;
	char	*tmp_for_join;
	int i;
	int k;

	i = -1;
	k = 0;
	while (str[++i] != '=' && str[i] != '+' && str[i])
	{
		if (is_ws(str[i]) == 1 || str[i] == '\0')
			return (ft_export_var_in_env(str, i, data), 0);
	}
	if (str[i] == '=')
		return (1);
	tmp = &data->env;
	var = ft_substr(str, 0, i);
	while (tmp->next && ft_strncmp(var, tmp->key, i))
		tmp = tmp->next;
	while (str[k + i + 1] && is_ws(str[k + i + 1]) == 0)
		k++;
	i = i + 2;
	if (ft_strncmp(var, tmp->key, i) == 0)
	{
		tmp_for_join = ft_strjoin(tmp->value, str + i);
		free(tmp->value);
		tmp->value = tmp_for_join;
		free(var);
	}
	else
	{
		tmp->next = ft_lstnew_env();
		tmp = tmp->next;
		tmp->key = var;
		tmp->value = ft_strdup(str + i);
		tmp->printable = 1;
	}
	return (0);
}

static int ft_verif_str_export(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]) == 1 || str[i] == '=' || str[i] == '+')
		return (1);
	while (str[++i] != '=' && str[i] != '+')
	{
		if (is_ws(str[i]) == 1 || str[i] == '\0')
			return (0);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	
	return (0);
}


static int ft_ok_export(char *str, t_data *data)
{
    t_env	*tmp;
	char	*var;
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '=')
	{
		if (is_ws(str[i]))
			return (0);
		i++;

	}	
	tmp = &data->env;
	var = ft_substr(str, 0, i);
	while (tmp->next && ft_strncmp(var, tmp->key, i))
		tmp = tmp->next;
	while (str[k + i + 1] && is_ws(str[k + i + 1]) == 0)
		k++;
	i = i + 1;
	if (ft_strncmp(var, tmp->key, i) == 0)
	{
		free(tmp->value);
		free(var);
		tmp->value = ft_strdup(str + i);
	}
	else
	{
		tmp->next = ft_lstnew_env();
		tmp = tmp->next;
		tmp->key = var;
		tmp->value = ft_substr(str, i, ft_strlen_WS(str + i));
		tmp->printable = 1;
	}
	return (0);
}

int ft_export(char **tab, t_data *data)
{
	int		i;
	char	*cmd;
	char	*str;

	i = 0;
	str = ft_tab_to_str(tab, ' ');
	// fprintf(stderr, "str = |%s|\n\n", str);
	ft_strlen_WS(str);
	if (ft_strncmp(str, "export", 7) == 0)
		return (ft_just_export(data));
	while (str[i] && str[i] != ' ')
		i++;
	i++;
	while (str[i])
	{
		if (ft_verif_str_export(str + i) == 1)
		{
			cmd = ft_substr(str, i, ft_strlen_WS(str + i));
			ft_printf("export: `%s': not a valid identifier\n", cmd);
			free(cmd);
		}
		else
		{
			if (ft_plus_egal_export(str + i, data) != 0)
				ft_ok_export(str + i, data);
		}
		i = i + ft_strlen_WS(str + i);
		while (str[i] && is_ws(str[i]) == 1)
			i++;
	}

	return (0);
}
// int main(int c, char **v, char **e)
// {
// 	// fprintf(stderr, "\n\n");
// 	ft_create_env(e);

//     char *test;
// 	test = "export";
//     fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export test=42";
//     fprintf(stderr, "\t\t\t\t\t\e[35m2|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export test+=pierretest";
//     fprintf(stderr, "\t\t\t\t\t\e[35m3|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export test_2+=pierretest";
//     fprintf(stderr, "\t\t\t\t\t\e[35m4|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export testspace=4  2 sansegal";
//     fprintf(stderr, "\t\t\t\t\t\e[35m5.1|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export testspace=4  2 sansegal PATH 54";
//     fprintf(stderr, "\t\t\t\t\t\e[35m5.2|%d|(%s)\e[0m\n", ft_export(test), test);
	
// 	test = "export testspace=4 2 sansegal PATH=test";
//     fprintf(stderr, "\t\t\t\t\t\e[35m5.3|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export testspace=4  2 test=test";
//     fprintf(stderr, "\t\t\t\t\t\e[35m5.4|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export test@=oui";
//     fprintf(stderr, "\t\t\t\t\t\e[35m6.1|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export 1a=b";
//     fprintf(stderr, "\t\t\t\t\t\e[35m6.2|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export test =oui";
//     fprintf(stderr, "\t\t\t\t\t\e[35m6.3|%d|(%s)\e[0m\n", ft_export(test), test);

// 	test = "export test +oui";
//     fprintf(stderr, "\t\t\t\t\t\e[35m6.4|%d|(%s)\e[0m\n", ft_export(test), test);

// 	ft_env();
// 	ft_free_env();
// }
