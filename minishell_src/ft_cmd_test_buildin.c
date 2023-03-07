#include "./inc/minishell.h"

int ft_exec_builtin(char **cmd, t_data *data)
{
	fprintf(stderr, "coucoucoucoucou\n\n");
	if (cmd && ft_strncmp(cmd[0], "env", 3) == 0)
		return(ft_env(data), 1);

	if (cmd && ft_strncmp(cmd[0], "export", 6) == 0)

		return (ft_export(cmd, data), 1);

	if (cmd && ft_strncmp(cmd[0], "echo", 4) == 0)
		return (ft_echo(cmd), 1);

	if (cmd && ft_strncmp(cmd[0], "cd", 2) == 0)
		return (ft_cd(cmd, data), 1);

	if (cmd && ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (ft_pwd(data), 1);

	if (cmd && ft_strncmp(cmd[0], "unset", 5) == 0)
		return (ft_unset(cmd, data), 1);
    return (0);
}

int ft_test_builtin(char **cmd)
{
	if (cmd && ft_strncmp(cmd[0], "env", 3) == 0)
		return (1);
	if (cmd && ft_strncmp(cmd[0], "export", 6) == 0)
		return (1);
	if (cmd && ft_strncmp(cmd[0], "echo", 4) == 0)
		return (1);
	if (cmd && ft_strncmp(cmd[0], "cd", 2) == 0)
		return (1);
	if (cmd && ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (1);
	if (cmd && ft_strncmp(cmd[0], "unset", 5) == 0)
		return (1);
    return (0);
}