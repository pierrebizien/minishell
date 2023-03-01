#include "./inc/minishell.h"

int ft_test_builtin(char *str, t_data *data)
{
	if (str && ft_strncmp(str, "env", 3) == 0)
		ft_env(data);
	if (str && ft_strncmp(str, "export", 6) == 0)
		ft_export(str, data);
	if (str && ft_strncmp(str, "echo", 4) == 0)
		ft_echo(str, data);
	if (str && ft_strncmp(str, "cd", 2) == 0)
		ft_cd(str, data);
	if (str && ft_strncmp(str, "pwd", 3) == 0)
		ft_pwd(data);
    return (0);
}