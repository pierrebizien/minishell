#include "../_Include/minishell.h"

int ft_exec_builtin(char **cmd, t_data *data)
{
	// ft_print_dchar(cmd);
	if (ft_strlen(cmd[0]) == 0)
		return (0);
	if (cmd && ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
		return(ft_env(data), 1);

	if (cmd && ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)

		return (ft_export(cmd, data), 1);

	if (cmd && ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
		return (ft_echo(cmd), 1);

	if (cmd && ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
		return (ft_exit(cmd, data), 1);

	if (cmd && ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		return (ft_cd(cmd, data), 1);

	if (cmd && ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
		return (ft_pwd(data), 1);

	if (cmd && ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		return (ft_unset(cmd, data), 1);

    return (0);
}

int ft_test_builtin(char **cmd)
{
	if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
		return (1);
    else
		return (0);
}