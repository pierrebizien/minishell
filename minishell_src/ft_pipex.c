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

int	ft_put_in(char **input)
{
	int	i;
	int	len;
	int	k;

	i = 0;
	len = 0;
	while (input[2][i] && (input[2][i] == '<' || is_ws(input[2][i])))
	{
		i++;
	}
	k = i;
	while (input[2][i] && !is_ws(input[2][i++]))
		len++;
	fprintf(stderr, "k vaut %d et len vaut %d\n", k, len);
	if (input[2][1] && input[2][1] != '<')
	{
		fprintf(stderr, "On rentre\n");
		free(input[1]);
		input[1] = ft_substr(input[2], k, len);
		if (!data.pip.infile)
			return (1);//GERER
		ft_memcpy(input[2], input[2] + i, len);
		// input[2][k + len + 1] = '\0';
	}
	return (0);
}

char	**ft_hd(char **input)
{
	char **output;
	int	i;
	int k;
	int j;

	i = 0;
	k = 0;
	j = 0;
	output = ft_calloc(ft_strstrlen(input) + 1, sizeof(char *));
	if (!output)
		return (NULL);
	while (input && input[i])
	{
		if (k == 1)
		{
			fprintf(stderr, "in[%d] = |%s|\n\n", k,  input[k]);
			output[k++] = ft_strdup("here_doc");
			i++;
		fprintf(stderr, "out[%d] = |%s|\n\n", k,  output[1]);
		}
		else if (k == 2)
		{
			while (is_ws(input[i][j]) || input[i][j] == '<')
				j++;
			output[k] = ft_substr(input[i],j , ft_strlen_WS(input[i] + j));
			k++;
		}
		else if (k == 3)
		{
			j = 0;
			while (input[i][j] && (is_ws(input[i][j]) || input[i][j] == '<'))
				j++;
			j++;
			while (input[i][j] && (!is_ws(input[i][j])))
				j++;
			j++;
			output[k] = ft_substr(input[i], j, ft_strlen(input[i] + j));
			i++;
			k++;
		}
		else
		{
			output[k] = ft_strdup(input[i]);
			free(input[i]);
			k++;
			i++;
		}


	}
	data.hd = 1;
	output[k] = 0;
	ft_print_dchar(output);
	return (output);

}

char	**ft_detect_in_out(char **input)
{
	int	i;

	i = 0;
	if (input[2][0] == '<')
	{
		if (input[2][1] == '<')
			input = ft_hd(input);
		else
			ft_put_in(input);
	}
	return (input);
}

void	ft_pipex(void)
{
    char **input;
	int		len;

	input = ft_generate_inp();
	len = ft_len_mpipe();
	ft_print_dchar(input);
	input = ft_detect_in_out(input);
	// ft_print_dchar(input);
	// fprintf(stderr, "len %d\n", len);
	// ft_print_dargs(input);
	pipex(len + 3 + data.hd, input, data.envp);

}