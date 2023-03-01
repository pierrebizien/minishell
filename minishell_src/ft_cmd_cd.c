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
			fprintf(stderr, "tmp->key = |%s|\t value = |%s|\n\n", tmp->key, tmp->value);
			return (ft_strdup(tmp->value));
		}
        tmp = tmp->next;
    }
    return (NULL);
}

int	ft_cd(char *str, t_data *data)
{
	DIR *dir;
	struct dirent *entrey;
	int i;
	char *path;
	(void) data;

	i = 3;
	if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
	{
		dir = opendir("/");
		path = ft_just_cd(data);
		if (path == NULL)
			return (write(1, "CHANGE ERROR HERE\n", 19));
		str = ft_strjoin("cd ", path);
		i++;
		fprintf(stderr, "path = %s\n", path);
	}
	else if (str[3] == '/')
	{
		dir = opendir("/");
		path = ft_strdup("/");
		i++;
	}
	else
	{
		dir = opendir(".");
		path = getcwd(NULL, 0);
		i = i + 1 + ft_strlen_char(str + i, '/');
	}
	entrey = readdir(dir);
	// fprintf(stderr, "str[%d] = |%s|\n", i, str + i);
	// fprintf(stderr, "path|%s|\n", path);
	while (entrey != NULL)
	{
		// fprintf(stderr, "name = (%d)|%s|\t%ld|%d\n", entrey->d_type, entrey->d_name, ft_strlen(entrey->d_name), ft_strlen_char(str + i, '/'));
		if (ft_strncmp(str + i, entrey->d_name, ft_strlen_char(str + i, '/')) == 0 && entrey->d_type == 4 && (int)ft_strlen(entrey->d_name) == ft_strlen_char(str + i, '/'))
		{
			// fprintf(stderr, "CHANGE = (%d)|%s|\n", entrey->d_type, entrey->d_name);
			i = i + 1 + ft_strlen_char(str + i, '/');
			free(path);
			path = ft_substr(str, 3, i - 3);
			// fprintf(stderr, "PATH = %s\t\tstr + %d = |%s|\n", path, i, ft_substr(str, 3, i - 3));
			closedir(dir);
			// fprintf(stderr, "str[%d] = |%s|\n", i, str + i);
			dir = opendir(path);

		}
		entrey = readdir(dir);

	}
	closedir(dir);
	if (ft_strncmp(path, str + 3, ft_strlen(str + 3)))
	{
		ft_putstr_fd("cd: ", 1);
		ft_putstr_fd(str + 3, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else
		fprintf(stderr, "OK\n");
	free(path);

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