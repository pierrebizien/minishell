#include "./inc/minishell.h"

t_data data;

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

size_t	ft_strlen_WS(const char *str)
{
	size_t	i;
	int		j;
	char	*ws;

	ws = WS;
	i = 0;
	while (str[i] && is_ws(str[i]) == 0)
		i++;
	return (i);
}

static int ft_just_export(void)
{
	t_env *tmp;

    tmp = &data.env;
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



static int ft_plus_egal_export(char *str)
{
    t_env	*tmp;
	char	*var;
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '=' && str[i] != '+' && str[i])
		i++;
	if (str[i] == '=')
		return (1);
	tmp = &data.env;
	var = ft_substr(str, 0, i);
	while (tmp->next && ft_strncmp(var, tmp->key, i))
		tmp = tmp->next;
	while (str[k + i + 1] && is_ws(str[k + i + 1]) == 0)
		k++;
	i = i + 2;
	if (ft_strncmp(var, tmp->key, i) == 0)
		tmp->value = ft_strjoin(tmp->value, str + i);
	else
	{
		tmp->next = ft_lstnew_env();
		tmp = tmp->next;
		tmp->key = var;
		tmp->value = ft_strdup(str + i);
	}
	return (0);
}

static int ft_verif_str_export(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[i]) == 1)
		return (1);
	while (str && str[++i] != '=' && str[i] != '+')
	{
		if (is_ws(str[i]))
		if(ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
	}
	if (str[i] == '+' && str[i + 1] != '=')
		return (1);
	
	return (0);
}


static int ft_ok_export(char *str, t_env *tmp)
{
	int j;
	int k;

	j = 0;
	while (str[j] != '=' && str[j])
		j++;
	k = 0;
	while (str[k + j + 1] && is_ws(str[k + j + 1]) == 0)
		k++;
	tmp->key = ft_substr(str, 0, j);
	if (!tmp->key)
		return (1);
	tmp->value = ft_substr(str, j+1, k);
	if (!tmp->key)
		return (1);
	tmp->next = NULL;
	return (0);
}

int ft_export(char *str)
{
    t_env	*tmp;
	int		i;

	i = 0;
	tmp = &data.env;
	ft_strlen_WS(str);
	if (ft_strncmp(str, "export", 7) == 0)
		return (ft_just_export());
	while (str[i] && str[i] != ' ')
		i++;
	i++;
	while (str[i])
	{
		if (ft_verif_str_export(str + i))
			ft_printf("export: `%s': not a valid identifier\n", ft_substr(str, i, ft_strlen_WS(str + i)));
		i = i + ft_strlen_WS(str + i);
		while (str[i] && is_ws(str[i]) == 1)
			i++;

	}
	if (ft_plus_egal_export(str + i) == 0)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_lstnew_env();
	tmp = tmp->next;
	ft_ok_export(str + i, tmp);

	return (0);
}

int main(int c, char **v, char **e)
{
	fprintf(stderr, "\n\n");
	ft_create_env(e);

    char *test;
	test = "export";
    fprintf(stderr, "\t\t\e[35m1|%d|\e[0m\n", ft_export(test));

	test = "export test=42";
    fprintf(stderr, "\t\t\e[35m2|%d|\e[0m\n", ft_export(test));

	test = "export test+=pierretest";
    fprintf(stderr, "\t\t\e[35m3|%d|\e[0m\n", ft_export(test));

	test = "export test_2+=pierretest";
    fprintf(stderr, "\t\t\e[35m4|%d|\e[0m\n", ft_export(test));

	test = "export testspace=4  2 sansegal";
    fprintf(stderr, "\t\t\e[35m5|%d|\e[0m\n", ft_export(test));

	test = "export testspace=4  2 test=test";
    fprintf(stderr, "\t\t\e[35m5.2|%d|\e[0m\n", ft_export(test));

	test = "export test@=oui";
    fprintf(stderr, "\t\t\e[35m6.1|%d|\e[0m\n", ft_export(test));

	test = "export 1test=oui";
    fprintf(stderr, "\t\t\e[35m6.2|%d|\e[0m\n", ft_export(test));

	test = "export test =oui";
    fprintf(stderr, "\t\t\e[35m6.3|%d|\e[0m\n", ft_export(test));

	test = "export test+ =oui";
    fprintf(stderr, "\t\t\e[35m6.4|%d|\e[0m\n", ft_export(test));



	// ft_env();
}