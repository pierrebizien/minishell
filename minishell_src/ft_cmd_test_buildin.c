#include "./inc/minishell.h"

int ft_test_builtin(char *str, t_data *data)
{
	if (str && ft_strncmp(str, "env", 3) == 0)
		return(ft_env(data), 1);
	if (str && ft_strncmp(str, "export", 6) == 0)
		return (ft_export(str, data), 1);
	if (str && ft_strncmp(str, "echo", 4) == 0)
		return (ft_echo(str, data), 1);
	if (str && ft_strncmp(str, "cd", 2) == 0)
		return (ft_cd(str, data), 1);
	if (str && ft_strncmp(str, "pwd", 3) == 0)
		return (ft_pwd(data), 1);
    return (0);
}