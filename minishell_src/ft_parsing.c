#include "minishell.h"

extern t_data data;
int ft_parse(char *str)
{
    data.args = ft_split(str, ' ');
    free(str);
}