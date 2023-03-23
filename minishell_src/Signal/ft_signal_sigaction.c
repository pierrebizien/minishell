/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_sigaction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:27:28 by ngriveau          #+#    #+#             */
/*   Updated: 2023/03/23 16:22:13 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_Include/minishell.h"

extern int	g_err_value;

void	ft_init_sigint(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_ctrlc;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
}

void	ft_init_sigint_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_ctrlc_exec;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_init_sigint_hd(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_ctrlc_hd;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	ft_init_sigquit_exec(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_ctrlb_exec;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ft_init_sigquit(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
