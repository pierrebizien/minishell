#include "../_Include/minishell.h"

void ft_free_env(t_data *data)
{
	t_env	*tmp;
	t_env	*adresse;

	tmp = &data->env;
	free(tmp->key);
	free(tmp->value);
	tmp = tmp->next;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		adresse = tmp->next;
		free(tmp);
		tmp = adresse;
	}
}