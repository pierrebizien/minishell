#include "./inc/minishell.h"

extern t_data data;

int ft_test_builtin(char *str)
{
	if (str && ft_strncmp(str, "env", 3) == 0)
		ft_env();
	if (str && ft_strncmp(str, "export", 6) == 0)
		ft_export(str);
    return (0);
}