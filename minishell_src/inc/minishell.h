/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:42:10 by pbizien           #+#    #+#             */
<<<<<<< HEAD:minishell_src/inc/minishell.h
/*   Updated: 2023/02/21 16:22:30 by ngriveau         ###   ########.fr       */
=======
/*   Updated: 2023/02/21 16:13:02 by pbizien          ###   ########.fr       */
>>>>>>> 43c94821a515410a378029525e1c1fdaf8719459:minishell/minishell.h
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../../libft/src/inc/SuperLibft.h"
# include <stdio.h>
<<<<<<< HEAD:minishell_src/inc/minishell.h
=======
// # include "../gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

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

>>>>>>> 43c94821a515410a378029525e1c1fdaf8719459:minishell/minishell.h

#endif