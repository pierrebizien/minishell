#include "inc/pipex_bonus.h"

void	ft_cut_redir(t_pipex *data, int len)
{
	if (data->param1 && !ft_strncmp(data->param1[len - 3], "<", ft_strlen(data->param1[len -2])))
		data->param1[len - 3] = 0;
	if (data->param1 && !ft_strncmp(data->param1[len - 2], "<", ft_strlen(data->param1[len -2])))
		data->param1[len - 2] = 0;
	if (data->param1)
		data->param1[len - 1] = 0;
}

int		ft_redir_first(t_pipex *data)
{
	int len;
	int	fd;
    len = ft_strstrlen(data->param1);
	if (!ft_strncmp(data->param1[len - 2], ">", ft_strlen(data->param1[len - 2])))
	{
		fd = open(data->param1[len -1],  O_RDWR | O_TRUNC | O_CREAT, 00644);
		if (fd == -1)
			return (printf("SORTIE"), perror("minishell"), -1);
		// dup2(fd, 1);
		ft_print_dchar(data->param1);
		ft_cut_redir(data, len);
		ft_print_dchar(data->param1);
		return (1);
	}
	else if (!ft_strncmp(data->param1[len - 2], ">>", ft_strlen(data->param1[len - 2])))
	{
		fd = open(data->param1[len -1],  O_RDWR | O_APPEND | O_CREAT, 00644);
		if (fd == -1)
			return (perror("minishell"), -1);
		// dup2(fd, 1);
		ft_cut_redir(data, len);
		return (1);
	}
	else
		return (0);
} 