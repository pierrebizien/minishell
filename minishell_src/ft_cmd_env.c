#include "./inc/minishell.h"


int ft_env(t_data *data)
{
    fprintf(stderr, "\n\n\nENV_BUILTIN\n\n\n");
    t_env *tmp;

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