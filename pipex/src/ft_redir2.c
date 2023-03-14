#include "inc/pipex_bonus.h"

char **ft_repl_ind_dchar(t_pipex *data, int ind, char **strstr)
{
    char **output;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
    output = malloc(sizeof(char *) * (ft_strstrlen(data->param1) + 1 + ft_strstrlen(strstr)));
	if (!output)
		return (NULL); //GERER
	while (data->param1 && data->param1[i])
	{
		if (i == ind)
		{
			while (strstr && strstr[j])
				output[k++] = ft_strdup(strstr[j++]);
			i++;
		}
		else
			output[k++] = ft_strdup(data->param1[i++]);
	}
	output[k] = 0;
	return (output);
}

int	ft_new_split_w_redir(t_pipex *data)
{
    int i;
	char **tmp;

	i = 0;
    while (data->param1 && data->param1[i])
	{

        if (contain_chev_out(data->param1[i]))
		{
            tmp = data->param1;
			data->param1 = ft_repl_ind_dchar(data, i, ft_split_k(data->param1[i], "><"));
			free(tmp);
		}
		i++;
    }
	return (0);
}