#include "../_Include/minishell.h"

extern int err_value;

int ft_exec_builtin(char **cmd, t_data *data, char **cmd_quotes)
{
	if (ft_strlen(cmd[0]) == 0)
		return (0);
	if (cmd && ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 3)
	{
		err_value = ft_env(cmd, data);
		return (1);
	}
	if (cmd && ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 6)
	{
		err_value = ft_export(cmd, data, cmd_quotes);
		return (1);
	}
	if (cmd && ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 4)
	{
		err_value = ft_echo(cmd, cmd_quotes);
		return (1);
	}
	if (cmd && ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 4)
	{
		err_value = ft_exit(cmd);
		return (1);
	}
	if (cmd && ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 2)
	{
		err_value = ft_cd(cmd, data);
		return (1);
	}
	if (cmd && ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 3)
	{
		err_value = ft_pwd(cmd, data);
		return (1);
	}
	if (cmd && ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 5)
	{
		err_value = ft_unset(cmd, data);
		return (1);
	}
	return (0);

}

int ft_test_builtin(char **cmd)
{
	if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 3)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 6)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 4)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 2)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 3)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 5)
		return (1);
	else if (ft_strlen(cmd[0]) != 0 && cmd && ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0 && ft_strlen(cmd[0]) == 4)
		return (1);
    else
		return (0);
}