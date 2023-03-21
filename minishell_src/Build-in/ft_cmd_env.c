#include "../_Include/minishell.h"


int ft_env(char **cmd, t_data *data)
{
    t_env *tmp;
    int i;

	i = 0;
    while (cmd && cmd[i])
	{
		if (cmd[i][0] == '-')
			return (ft_putstr_fd("Error env: ", 2), ft_putstr_fd(cmd[i], 2), ft_putstr_fd(": invalid option\n", 2), 125);
		i++;
	}
    tmp = &data->env;
    while (tmp)
    {
        if (tmp->printable == 1)
        {
            write(1, tmp->key, ft_strlen(tmp->key));
            write(1, "=", 1);
            write(1, tmp->value, ft_strlen(tmp->value));
            write(1, "\n", 1);
        }
        tmp = tmp->next;
    }
    return (0);
}

//