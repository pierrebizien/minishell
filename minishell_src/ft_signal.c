#include "./inc/minishell.h"

void	ft_ctrlc(int a)
{
	fprintf(stderr, "CONTROLE C %d\n", a);
	return ;
}