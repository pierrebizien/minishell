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
		{
			// fprintf(stderr, "tmp->key = |%s|\t value = |%s|\n\n", tmp->key, tmp->value);
			return (ft_strdup(tmp->value));
		}
        tmp = tmp->next;
    }
    return (NULL);
}

char *ft_change_pwd(t_data *data)
{
    t_env *tmp;
	int changepwd;

    tmp = &data->env;
	changepwd = 0;
    while (tmp)
    {
        // if (ft_strncmp(tmp->key, "PWD", ft_strlen(tmp->key)) == 0)
		// {
		// 	// if (ft_strncmp(tmp->value,getcwd(NULL, 0) )
		// 	// fprintf(stderr, "tmp->key = |%s|\t value = |%s|\tpwd = %s\n\n", tmp->key, tmp->value, getcwd(NULL, 0));
		// }
        tmp = tmp->next;
    }
	tmp = &data->env;
    while (tmp && changepwd == 1)
    {
		if (ft_strncmp(tmp->key, "OLDPWD", ft_strlen(tmp->key)) == 0)
		{
			fprintf(stderr, "tmp->key = |%s|\t value = |%s|\n\n", tmp->key, tmp->value);
		}
        tmp = tmp->next;
    }
    return (NULL);
}

int	ft_cd(char *strr, t_data *data)
{
	// DIR *dir;
	// struct dirent *entrey;
	int i;
	char *path;
	char **str = ft_split(strr, ' ');

	
	fprintf(stderr, "pwd = %s\n", getcwd(NULL, 0));
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
	

	// chdir(NULL);


	return (0);
}
// int main(void)
// {
	// char *test;
	// test = "cd";
    // fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_cd(test, NULL), test);

	// test = "cd /";
    // fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_cd(test, NULL), test);

	// test = "cd /mnt/nfs/homes/ngriveau/Desktop/";
    // fprintf(stderr, "\t\t\t\t\t\e[35m2|%d|(%s)\e[0m\n", ft_cd(test, NULL), test);

	// test = "cd ./libft";
    // fprintf(stderr, "\t\t\t\t\t\e[35m3|%d|(%s)\e[0m\n", ft_cd(test, NULL), test);

	// test = "cd /mnt/caca/";
    // fprintf(stderr, "\t\t\t\t\t\e[35m4|%d|(%s)\e[0m\n", ft_cd(test, NULL), test);


// }