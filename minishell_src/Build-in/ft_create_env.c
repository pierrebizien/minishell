#include "../_Include/minishell.h"

t_env	*ft_lstnew_env(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void ft_modif_SHLVL(t_env *tmp)
{
	int nb;

	nb = ft_atoi(tmp->value);
	free(tmp->value);
	tmp->value = ft_itoa(nb + 1);

}

int ft_create_env(char **envp, t_data *data)
{
	int i;
	int j;
	int k;
	t_env	*tmp;

	i = -1;
	tmp = &data->env;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j])
			j++;
		k = 0;
		while (envp[i][k + j + 1])
			k++;
		tmp->key = ft_substr(envp[i], 0, j);
		if (!tmp->key)
			return (1);
		tmp->value = ft_substr(envp[i], j + 1, k);
		if (!tmp->key)
			return (1);
		tmp->printable = 1;
		if (ft_strncmp(tmp->key, "SHLVL",6 ) == 0)
			ft_modif_SHLVL(tmp);
		if (envp[i + 1])
		{
			tmp->next = ft_lstnew_env();
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
	}
	return (0);
}