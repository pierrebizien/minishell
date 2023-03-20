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

	// ft_print_list(begin);

	while (tmp)
	{
		if (tmp->hd_filename != NULL)
		{
			unlink(tmp->hd_filename);
		}
		tmp = tmp->next;
	}
	
}

void	ft_free_list(t_exec *begin)
{
	t_exec *tmp;

	while (begin)
	{
		if (begin->next)
			tmp = begin->next;
		if (begin->str != NULL)
			free(begin->str);
		if (begin->hd_filename != NULL)
			free(begin->hd_filename);
		// free(begin);
		begin = tmp;
	}
}

void ft_free_end(t_data *data)
{
	free(data->pwd);
	free(data->oldpwd);
	// ft_free_list(&data->exec);
	ft_free_env(data);
}