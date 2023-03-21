#include "../_Include/minishell.h"

static int ft_just_export(t_data *data)
{
	t_env *tmp;

    tmp = &data->env;
    while (tmp)
    {
		write(1, "export ", 7);
        write(1, tmp->key, ft_strlen(tmp->key));
        write(1, "=\"", 2);
        write(1, tmp->value, ft_strlen(tmp->value));
        write(1, "\"\n", 2);
        tmp = tmp->next;
    }
	return (0);
}

size_t	ft_strlen_WS(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && is_ws(str[i]) == 0)
		i++;
	return (i);
}

static int ft_ok_export(char *str, t_data *data, char **cmd_quotes)
{
    t_env	*tmp;
	char	*var;
	int i;
	int k;
(void) cmd_quotes;


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
	while (tmp->next && ft_strncmp(var, tmp->key, i+1))
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
static int ft_plus_egal_export(char *str, t_data *data, char **cmd_quotes)
{
    t_env	*tmp;
	char	*var;
	char	*tmp_for_join;
	int i;
	int k;
(void) cmd_quotes;


	i = -1;
	k = 0;
	while (str[++i] != '=' && str[i] != '+' && str[i])
	{
		if (is_ws(str[i]) == 1 || str[i+1] == '\0')
			return (0);
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
	if (ft_isdigit(str[i]) == 1 || str[i] == '=' || str[i] == '/' || str[i] == '\0' || str[i] == '+' || str[i] == '$' || (str[0] == '-' && (str[1] == '\0' || str[1] == '\0')))
		return (0);
	while (str[++i] != '=' && str[i] != '+')
	{
		if (is_ws(str[i]) == 1 || str[i] == '\0')
			return (1);
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (0);
	if (str[i] == '=')
		return (2);
	if (str[i] == '+')
		return (3);
	return (1);
}

int	ft_verif_option_export(char **cmd, char **cmd_quotes)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		if (cmd_quotes[i][0] == 1)
			i++;
		else if (cmd[i][0] == '-' && (cmd[i][1] != '\0' || cmd[i][1] != '\0'))
			return (ft_putstr_fd("export: usage: export [name[=value] ...] (no option)\n", 2), 1);
		else 
			i++;
	}
	return (0);
}


int ft_export(char **cmd, t_data *data, char **cmd_quotes)
{
	int		i;
	int		error;

	i = 1;
	error = 0;
	// ft_print_dchar(cmd);
	// ft_print_dchar(cmd_quotes);
	if (ft_verif_option_export(cmd, cmd_quotes))
		return (2);
	if (ft_strstrlen(cmd) == 1)
		return (ft_just_export(data));
	while (cmd[i])
	{
		// fprintf(stderr, "|%s| = %d\n", cmd[i], ft_verif_str_export(cmd[i]));
		if (ft_verif_str_export(cmd[i]) == 0)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			error = 1;
		}
		else if (ft_verif_str_export(cmd[i]) == 1)
			ft_putstr_fd("exporting a local variable is not possible\n", 2);
		else if (ft_verif_str_export(cmd[i]) == 2)
			ft_ok_export(cmd[i], data, cmd_quotes);
		else if (ft_verif_str_export(cmd[i]) == 3)
			ft_plus_egal_export(cmd[i], data, cmd_quotes);
		i++;
	}

	return (error);
}








// export lol='$lol' echo $lol


// static int ft_verif_str_export(char *str)
// {
// 	int i;

// 	i = 0;
// 	fprintf(stderr, "str = %s\n", str);
// 	if (ft_isdigit(str[i]) == 1 || str[i] == '=' || str[i] == '+' || str[i] == '$')
// 		return (1);
// 	while (str[++i] != '=' && str[i] != '+')
// 	{
// 		if (is_ws(str[i]) == 1 || str[i] == '\0')
// 			return (0);
// 		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
// 			return (1);
// 	}
// 	if (str[i] == '+' && str[i + 1] != '=')
// 		return (1);
	
// 	return (0);
// }


// static int ft_ok_export(char *str, t_data *data)
// {
//     t_env	*tmp;
// 	char	*var;
// 	int i;
// 	int k;

// 	i = 0;
// 	k = 0;
// 	while (str[i] != '=')
// 	{
// 		if (is_ws(str[i]))
// 			return (0);
// 		i++;
// 	}	
// 	tmp = &data->env;
// 	var = ft_substr(str, 0, i);
// 	while (tmp->next && ft_strncmp(var, tmp->key, i+1))
// 		tmp = tmp->next;
// 	while (str[k + i + 1] && is_ws(str[k + i + 1]) == 0)
// 		k++;
// 	i = i + 1;
// 	if (ft_strncmp(var, tmp->key, i) == 0)
// 	{

// 		free(tmp->value);
// 		free(var);
// 		tmp->value = ft_strdup(str + i);
// 	}
// 	else
// 	{
// 		tmp->next = ft_lstnew_env();
// 		tmp = tmp->next;
// 		tmp->key = var;
// 		tmp->value = ft_substr(str, i, ft_strlen_WS(str + i));
// 		tmp->printable = 1;
// 	}
// 	return (0);
// }

// int	ft_verif_option_export(char *str)
// {
// 	int i;
// 	int dq;
// 	int sq;

// 	i = 0;
// 	sq = -1;
// 	dq = -1;
// 	while (str[i])
// 	{
// 		fprintf(stderr, "str[%d] = %c\n", i, str[i]);
// 		ft_maj_quotes(&dq, &sq, str[i]);
// 		if (sq == 1 || dq == 1)
// 			i++;
// 		else if (is_ws(str[i]) && str[i+1] == '-')
// 			return (ft_putstr_fd("export: usage: export [name[=value] ...] (no option)\n", 2), 1);
// 		else 
// 			i++;
// 	}
// 	return (0);
// }

// int ft_export(char **tab, t_data *data)
// {
// 	int		i;
// 	char	*cmd;
// 	char	*str;

// 	i = 0;
// 	ft_print_dchar(tab);
// 	str = ft_tab_to_str(tab, ' ');
// 	if (ft_verif_option_export(str))
// 		return (0);
// 	ft_strlen_WS(str);
// 	if (ft_strncmp(str, "export", 7) == 0)
// 		return (free(str), ft_just_export(data));
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	i++;
// 	while (str[i])
// 	{
// 		if (ft_verif_str_export(str + i) == 1)
// 		{
// 			cmd = ft_substr(str, i, ft_strlen_WS(str + i));
// 			ft_printf("export: `%s': not a valid identifier\n", cmd);
// 			free(cmd);
// 		}
// 		else
// 		{
// 			if (ft_plus_egal_export(str + i, data) != 0)
// 				ft_ok_export(str + i, data);
// 		}
// 		i = i + ft_strlen_WS(str + i);
// 		while (str[i] && is_ws(str[i]) == 1)
// 			i++;
// 	}
// 	free(str);
// 	return (0);
// }
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
	
// 	test = "export testspace=4 2 sansegal USER=test";
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

