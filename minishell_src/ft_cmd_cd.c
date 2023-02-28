#include "./inc/minishell.h"
#include <sys/types.h>
#include <dirent.h>

extern t_data data;

int ft_strlen_char(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

int	ft_cd(char *str)
{
	DIR *dir;
	struct dirent *entrey;
	int i;
	char *path;


	i = 3;
	if (str[3] == '/')
	{
		dir = opendir("/");
		i++;
	}
	else
		dir = opendir(".");
	// entrey = readdir(dir);
	// fprintf(stderr, "str[%d] = |%s|\n", i, str + i);
	i = i + ft_strlen_char(str + i, '/');
	dir = opendir(path);

	while (entrey != NULL)
	{

		fprintf(stderr, "name = (%d)|%s|\n", entrey->d_type, entrey->d_name);
		if (ft_strncmp(str + i, entrey->d_name, ft_strlen_char(str + i, '/')) == 0 && entrey->d_type == 4 && ft_strlen(entrey->d_name) == ft_strlen_char(str + i, '/'))
		{
			fprintf(stderr, "CHANGE = (%d)|%s|\n", entrey->d_type, entrey->d_name);
			path = ft_substr(str, 3, i - 3);
			fprintf(stderr, "PATH = %s\n", path);
			closedir(dir);
			i = i + ft_strlen_char(str + i, '/');
			fprintf(stderr, "str[%d] = |%s|\n", i, str + i);
			dir = opendir(path);
			// free(path);

		}
		entrey = readdir(dir);

	}
	closedir(dir);

	return (0);
}
int main(void)
{
	char *test;
	// test = "cd /";
    // fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_cd(test), test);

	// test = "cd /mnt/nfs/homes/ngriveau/Desktop/minishell";
    // fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_cd(test), test);

	test = "cd ./libft";
    fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_cd(test), test);

	// test = "cd /mnt/nfs/";
    // fprintf(stderr, "\t\t\t\t\t\e[35m1|%d|(%s)\e[0m\n", ft_cd(test), test);
}