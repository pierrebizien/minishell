#include "./minishell.h"

extern t_data data;

int	ft_len_mpipe()
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (data.args && data.args[i])
	{
		if (ft_strncmp(data.args[i], "|", ft_strlen(data.args[i]) + 1))
			count++;
		i++;
	}
	return (count);
	

}

char **ft_generate_inp()
{
	char	**output;
	int		i;
	int		k;

    i = 0;
	k = 2;
	output = ft_calloc(ft_len_mpipe() + 4, sizeof(char *));
	if (!output)
		return (NULL); // PENSER A FREE
	output[0] = ft_strdup("./pipex");
	// fprintf(stderr, "coucou\n");
	while (data.args && data.args[i])
	{
		if (ft_strncmp(data.args[i], "|", ft_strlen(data.args[i]) + 1))
		{
			output[k++] = ft_strdup(data.args[i]);
			if (!output[k - 1])
				return (NULL); //PENSER A FREE
		}
		i++;
	}
	output[1] = ft_strdup(data.pip.infile);
	output[k++] = ft_strdup(data.pip.outfile);
	output[k] = 0;
	if (!output[0] || !output[k - 1])
		return (NULL); //PENSER A FREE
	return (output);
}

void	ft_pipex(void)
{
    char **input;
	int							len;

	input = ft_generate_inp();
	len = ft_len_mpipe();
	// fprintf(stderr, "len %d\n", len);
	// ft_print_dargs(input);
	pipex(len + 3, input, data.envp);

}