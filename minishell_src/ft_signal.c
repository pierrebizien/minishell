#include "./inc/minishell.h"

void	ft_ctrlc(int a)
{
	(void)a;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	ft_ctrlb(int a)
{
	(void)a;
	// rl_on_new_line();
	rl_replace_line("minishell > ", 0);
	rl_redisplay();
}
