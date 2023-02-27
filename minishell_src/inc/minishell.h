
#ifndef MINISHELL_H

# define MINISHELL_H

# include "../../libft/src/inc/SuperLibft.h"
# include "../../pipex/src/inc/pipex_bonus.h"

# include <stdio.h>
// # include "../gnl/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>

#define WS " \t\n\f\v\r"
#define MALLOC_ERROR "erreur de malloc"
#define MAL_ERCODE 42

void    ft_logo(void);

typedef	struct	s_env
{
    char			*key;
	char			*value;
	struct s_env	*next;
	
}               t_env;

typedef struct	s_pip
{
	char	*infile;
	char	*outfile;
}				t_pip;

typedef	struct	s_data
{
	t_env	env;
	t_pip	pip;
    char 	**args;
	char 	**av;
	char **envp;
	int		ac;
	char	*sep;
	
}               t_data;


//FT_PARSING

char	*ft_parse(char *str);

//FT_INIT

int ft_init(char **argv, char **envp, int ac);

//FT_ENV
t_env	*ft_lstnew_env(void);
int	ft_create_env(char **envp);
int ft_env(void);

//FT_TEST_BUILDTIN
int ft_test_builtin(char *str);


void	ft_ctrlb(int a);
void	ft_ctrlc(int a);

char	**ft_split_k(char const *s, char *sep);
char	**ft_split_l(char const *s, char *sep);

//FT_FREE
// void ft_free_dchar(char **s);
char	**ft_split_l(char const *s, char *sep);
void	ft_print_dargs(char **strstr);

int	ft_in_q(int in_q);

//FT_PIPEX
void	ft_pipex(void);


// int	pipex(int ac, char **av, char **envp);



#endif