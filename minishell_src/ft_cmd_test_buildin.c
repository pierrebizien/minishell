#include "./inc/minishell.h"

int ft_test_builtin(char *str, t_data *data)
{
	// fprintf(stderr, "\n\n start pwd = %s\ndata pwd = %s\nold = %s", getcwd(NULL, 0), data->pwd, data->oldpwd);

	if (str && ft_strncmp(str, "env", ft_strlen(str)) == 0)
		ft_env(data);
	if (str && ft_strncmp(str, "export", ft_strlen(str)) == 0)
		ft_export(str, data);
	if (str && ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		ft_echo(str, data);
	if (str && ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		ft_cd(str, data);
	if (str && ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		ft_pwd(data);
	if (str && ft_strncmp(str, "unset", 5) == 0)
		ft_unset(str, data);
		
	// fprintf(stderr, "\n\n end pwd = %s\ndata pwd = %s\nold = %s", getcwd(NULL, 0), data->pwd, data->oldpwd);

    return (0);
}