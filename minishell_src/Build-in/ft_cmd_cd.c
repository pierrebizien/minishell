#include "../_Include/minishell.h"
#include <sys/types.h>
#include <dirent.h>


int ft_strlen_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char *ft_just_cd(t_data *data)
{
    t_env *tmp;

    tmp = &data->env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "HOME", ft_strlen(tmp->key)) == 0)
			return (ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}

void	ft_change_pwd(t_data *data)
{
	t_env *tmp;

    tmp = &data->env;
	
	if (ft_strcmp(data->pwd, getcwd(NULL, 0)) == 0)
		return ;
	free(data->oldpwd);
	data->oldpwd = ft_strdup(data->pwd);	
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	// fprintf(stderr, "data->pwd = |%s|\n", data->pwd);
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(data->pwd);
		}
		if (ft_strncmp(tmp->key, "OLDPWD", ft_strlen(tmp->key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(data->oldpwd);
		}
        tmp = tmp->next;
    }
}

int	ft_cd(char **str, t_data *data)
{
	// DIR *dir;
	// struct dirent *entrey;
	int i;
	char *path;
	path = NULL;

	if (ft_strstrlen(str) == 1)
	{
		path = ft_just_cd(data);
		if (chdir(path) != 0)
			return (perror(path), 1);
	}
	else
	{
		i = 1;
		if (str[i][0] == '-')
			return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(str[i], 2), ft_putstr_fd(": invalid option", 2), 2);
		if (str[i] == 0)
			return (0);
		if (ft_strstrlen(str) != i + 1)
			return (ft_putstr_fd("cd: too many arguments\n", 2), 1);	
		if (chdir(str[i]) != 0)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(str[i], 2);
			ft_putstr_fd(": ", 2);
			return (perror(path), 1);
		}
	}
	ft_change_pwd(data);
	return (0);
}
