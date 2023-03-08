#include "./inc/minishell.h"

int	ft_unset(char **str, t_data *data)
{
	int i;
    t_env *before;
    t_env *tmp;
    t_env *after;

	if (ft_strstrlen(str) == 1)
		return (0);
	i = 1;
	while (str[i][0] == '-')
		i++;
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
