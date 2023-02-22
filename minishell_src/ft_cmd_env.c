#include "./inc/minishell.h"

extern t_data data;

int ft_env(void)
{
    t_env *tmp;

    tmp = &data.env;
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