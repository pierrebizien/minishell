#include "./inc/minishell.h"

extern t_data data;


int ft_1st_chev(void)
{
    if (data.ac <= 2)
        return (write(2, "syntax error\n", 13), 2);
	// if (data.ac == 3)
    return (0);
}

int ft_detect(void)
{
    if (data.args && ft_strncmp(data.args[0], "<", ft_strlen(data.args[0])) == 0)
    {
        return (ft_1st_chev());
    }
    return (0);
}

int ft_parse(char *str)
{
    data.args = ft_split(str, ' ');
    if (!data.args)
        return (1);
    // free(str);
    return(ft_detect());
    return (0);
}