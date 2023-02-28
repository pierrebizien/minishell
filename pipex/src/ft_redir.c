#include "inc/pipex_bonus.h"

int		ft_redir_first(t_pipex *data)
{
	int len;
	int	fd;

    len = ft_strstrlen(data->param1);
	if (ft_strncmp(data->param1[len - 2], ">", ft_strlen(data->param1[len - 2])))
	{
		fd = open(data->param1[len -1],  O_RDWR | O_TRUNC | O_CREAT, 00644);
		if (fd == -1)
			return (perror("minishell"), -1);
		dup2(fd, 1);
		return (1);
	}
	else if (ft_strncmp(data->param1[len - 2], ">>", ft_strlen(data->param1[len - 2])))
	{
		fd = open(data->param1[len -1],  O_RDWR | O_APPEND | O_CREAT, 00644);
		if (fd == -1)
			return (perror("minishell"), -1);
		dup2(fd, 1);
		return (1);
	}
	
	else
		return (0);
}