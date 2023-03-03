#include "./inc/minishell.h"
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
	char *path;
	char *pwd;

	path = getcwd(NULL, 0);
    tmp = &data->env;
	pwd = NULL;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
		{
			pwd = tmp->value;
			tmp->value = path;
		}
        tmp = tmp->next;
    }
    tmp = &data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", ft_strlen(tmp->key)) == 0 && pwd != NULL)
		{
			free(tmp->value);
			tmp->value = pwd;
		}
        tmp = tmp->next;
	}
}

int	ft_cd(char *strr, t_data *data)
{
	// DIR *dir;
	// struct dirent *entrey;
	int i;
	char *path;
	char **str = ft_split(strr, ' '); // a changer

	if (ft_strstrlen(str) == 1)
	{
		path = ft_just_cd(data);
		if (chdir(path) != 0)
			return (perror(path), 1);
	}
	else
	{
		i = 1;
		while (str[i][0] == '-')
			i++;
		if (str[i] == 0)
			return (0);
		if (chdir(str[i]) != 0)
			return (perror(path), 1);
	}
	ft_change_pwd(data);
	return (0);
}
