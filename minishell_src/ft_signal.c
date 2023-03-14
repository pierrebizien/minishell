#include "./inc/minishell.h"
extern int err_value;

void	ft_ctrlc(int a)
{
	(void)a;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
void	ft_ctrlc_exec(int a)
{
	(void)a;
	write(1, "\n", 2);
	return ;
}

void	ft_ctrlc_hd(int a)
{
	(void)a;
	err_value = 130;
	rl_done = 1;
	return ;
}

void	ft_ctrlb_exec(int a)
{
	(void)a;
	ft_putstr_fd("Quit (core dumped)\n", 2);
	return ;
}

void	ft_ctrlb(int a)
{
	(void)a;
	rl_redisplay();  //
}

