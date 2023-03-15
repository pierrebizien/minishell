#include "./minishell.h"

// void ft_free_dchar(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str && str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free (str);
// }

void	ft_unlink_hd(t_exec *begin)
{
	t_exec *tmp;

	tmp = begin;
	while (tmp)
	{
		if (begin->hd_filename != NULL)
		{
			unlink(begin->hd_filename);
		}
		tmp = tmp->next;
	}
	
}