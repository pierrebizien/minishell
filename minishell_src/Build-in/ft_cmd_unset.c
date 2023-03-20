#include "../_Include/minishell.h"



int	ft_verif_option_unset(char *str)
{
	int i;
	int dq;
	int sq;

	i = 0;
	sq = -1;
	dq = -1;
	while (str[i])
	{
		fprintf(stderr, "str[%d] = %c\n", i, str[i]);
		ft_maj_quotes(&dq, &sq, str[i]);
		if (sq == 1 || dq == 1)
			i++;
		else if (is_ws(str[i]) && str[i+1] == '-')
			return (ft_putstr_fd("export: usage: export [name[=value] ...] (no option)\n", 2), 1);
		else 
			i++;
	}
	return (0);
}

int	ft_unset(char **str, t_data *data)
{
	int i;
    t_env *before;
    t_env *tmp;
    t_env *after;

	if (ft_strstrlen(str) == 1)
		return (0);
	i = 1;
	while (str && str[i])
	{
		if (str[i][0] == '-')
			return (ft_putstr_fd("unset: usage: unset [name[=value] ...] (no option)\n", 2), 2);
		i++;
	}
	i = 1;
	while (str[i] != 0)
	{
		tmp = &data->env;
		before = NULL;
		while (tmp)
		{
			if (ft_strncmp(tmp->key, str[i], ft_strlen(str[i])) == 0)
			{
				after = tmp->next;
				free(tmp->key);
				free(tmp->value);
				if (before == NULL)
					data->env = *after;
				else if (after == NULL)
				{
					free(tmp);
					before->next = NULL;
				}
				else
				{
					free(tmp);
					before->next = after;
				}
				break;
			}
			before = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
