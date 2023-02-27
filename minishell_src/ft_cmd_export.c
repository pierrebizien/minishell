#include "./inc/minishell.h"

t_data data;


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

	i = 0;
	while (str[i] != '=' && str[i] != '+' && str[i])
		i++;
	if (str[i] == '=')
		return (1);
	tmp = &data.env;
	var = ft_substr(str, 0, i);
	// fprintf(stderr, "var = |%s|%s|%d\n\n", var,str + i + 2,  i);
	while (tmp->next && ft_strncmp(var, tmp->key, i))
		tmp = tmp->next;
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

	i = -1;
	while (str && str[++i] != '=' && str[i] != '+')
	{
		if(ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
	}
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
	while (str[k + j + 1])
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
	if (ft_strncmp(str, "export", 7) == 0)
		return (ft_just_export());
	while (str[i] && str[i] != ' ')
		i++;
	i++;
	if (ft_verif_str_export(str + i) == 1)
		return (ft_printf("export: `%s': not a valid identifier", str), 1);
	if (ft_plus_egal_export(str + i) == 0)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_lstnew_env();
	tmp = tmp->next;
	ft_ok_export(str + i, tmp);
	return (0);

}