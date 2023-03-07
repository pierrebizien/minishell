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
	fprintf(stderr, "coucoucoucoucoucou\n");
	while (str[i] != 0)
	{
		tmp = &data->env;
		before = NULL;
		while (tmp)
		{
			// fprintf(stderr, "str[%d] = %s\n", i, str[i]);
			// fprintf(stderr, "key = %s\t value = %s\n", tmp->key, tmp->value);
			if (ft_strncmp(tmp->key, str[i], ft_strlen(str[i])) == 0)
			{
				// fprintf(stderr, "tmp->key = %s\t tnp->value = %s\n\n", tmp->key, tmp->value);
				after = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				// fprintf(stderr, "tmp->key = %s\t tnp->value = %s\n\n", tmp->key, tmp->value);
				if (before == NULL)
				{
					data->env = *after;
				}
				else if (after == NULL)
				{
					before->next = NULL;
				}
				else
				{
					fprintf(stderr, "after->key = %s\tbefore->key = %s\t tmp->key = %s\n\n", after->key, before->key, tmp->key);
					before->next = after;
				}
				break;
			}
			before = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	tmp = &data->env;
    while (tmp)
    {

    	write(1, tmp->key, ft_strlen(tmp->key));
		write(1, "=", 1);
		write(1, tmp->value, ft_strlen(tmp->value));
		write(1, "\n", 1);
    	tmp = tmp->next;
    }
	return (0);
}
