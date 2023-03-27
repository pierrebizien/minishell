/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:27:28 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/27 16:06:01 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_ctrlc(int a)
{
	(void)a;
	g_err_value = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	ft_ctrlc_exec(int a)
{
	(void)a;
	g_err_value = 130;
	return ;
}

void	ft_ctrlc_hd(int a)
{
	(void)a;
	g_err_value = 130;
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
	rl_redisplay();
}
