#include "./inc/minishell.h"

extern t_data data;

int ft_echo(int start, int end)
{
    int newline;
    if (data.args[start] == 0)
        return (0);
}

int main(void)
{
    char *cmd;
    cmd = "echo -n test numero 1";
    ft_echo(1, 4);
}
