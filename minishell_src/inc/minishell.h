/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:42:10 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/21 18:11:35 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../../libft/src/inc/SuperLibft.h"
# include <stdio.h>
// # include "../gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

void    ft_logo(void);

typedef	struct	s_data
{
    char 	**args;
	char 	**av;
	char 	**envp;
	int		ac;
	
}               t_data;


//FT_PARSING

int ft_parse(char *str);

//FT_INIT

int ft_init(char **argv, char **envp, int ac);

void	ft_ctrlc(int a);

#endif