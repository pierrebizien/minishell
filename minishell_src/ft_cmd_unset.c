#include "./inc/minishell.h"

int	ft_unset(char *strr, t_data *data)
{
	int i;
    t_env *before;
    t_env *tmp;
    t_env *after;


	char **str = ft_split(strr, ' '); // a changer

	if (ft_strstrlen(str) == 1)
		return (0);
	i = 1;
	while (str[i][0] == '-')
		i++;
	while (str[i] != 0)
	{
		// fprintf(stderr, "str[%d] = |%s|\n", i, str[i]);
		tmp = &data->env;
		before = NULL;
		while (tmp)
		{
			// fprintf(stderr, "key = %s\t value = %s\n", tmp->key, tmp->value);
			if (ft_strncmp(tmp->key, str[i], ft_strlen(str[i])) == 0)
			{
				// fprintf(stderr, "ca change after = %p\n", after);
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
