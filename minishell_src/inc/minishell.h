
#ifndef MINISHELL_H

# define MINISHELL_H

# include "../../libft/src/inc/SuperLibft.h"
// # include "../../pipex/src/inc/pipex_bonus.h"

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
# include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WS " \t\n\f\v\r"
#define MALLOC_ERROR "erreur de malloc"
#define MAL_ERCODE 42


#define F_INFILE 0
#define F_DELIMITER 1
#define F_FALSEI 2
#define F_FALSED 3

#define F_PIPE 5

#define F_CMD 10

#define F_APPEND 6
#define F_TRONC 7
#define F_FALSEA 8
#define F_FALSET 9



void    ft_logo(void);

typedef	struct	s_env
{
	int				printable;
    char			*key;
	char			*value;
	struct s_env	*next;
	
}               t_env;

typedef struct	s_exec
{
	char			*str;
	int				id;
	int				touch;
	struct s_exec	*next;
	struct s_exec	*prev;

}				t_exec;

typedef	struct	s_pip
{
	int		fd_in;
	int		last_id;
	int		hd_in;
	int		fd_out;
	int		nb_pipes;
	int		tmp_fd;
	int		pipefd1[2];
	int		pipefd2[2];
}				t_pip;


typedef	struct	s_data
{
	t_env	env;
	t_exec	exec;
	t_pip	pip;
    char 	**args;
	int		ac;
	char 	**av;
	char	**envp;
	char	*sep;
	int		hd;
	char	*pwd;
	char	*oldpwd;
	int		err_built_in;
	int		last_err_num;
	char	*last_err_str;
	
}               t_data;


//FT_PARSING
void	ft_parse_for_exec(t_data *data);
char	*ft_parse(char *str, t_data *data);
int		is_ws(char c);


//FT_INIT

int ft_init(char **env, t_data *data);

//FT_ENV 42
int		ft_create_env(char **envp, t_data *data);
t_env	*ft_lstnew_env(void);
void	ft_free_env(t_data *data);
int		ft_env(t_data *data);


//FT_UNSET
int		ft_unset(char **strr, t_data *data);

//FT_EXPORT
int		ft_export(char **str, t_data *data);

// FT_ECHO
int		ft_echo(char **cmd);

// FT_PWD
int		ft_pwd(t_data *data);

// FT_CD
int		ft_cd(char **str, t_data *data);

//FT_TEST_BUILDTIN
int		ft_test_builtin(char **str);
int ft_exec_builtin(char **cmd, t_data *data);



void	ft_ctrlb(int a);
void	ft_ctrlc(int a);

void	ft_print_dchar(char **strstr);


char	**ft_split_k(char const *s, char *sep);
char	**ft_split_l(char const *s, char *sep);


//FT_FREE
char	**ft_split_l(char const *s, char *sep);
void	ft_print_dargs(char **strstr);

int	ft_in_q(int in_q);

//FT_PIPEX
void	ft_pipex(t_data *data);

//FT_UTILS
int		ft_strstrlen(char **strstr);
size_t	ft_strlen_WS(const char *str);
char *ft_put_str_in_str(char *dest, char *src, int ind);

//FT_HEREDOC
int	ft_heredoc(t_data *data, char *delimiter, int w);
void	ft_close(int *fd);
void	ft_init_pipex_pipe(t_data *data);


//PIPEX_UTILS
void	ft_free_dchar(char **str);
char    *ft_strrjoin(char const *s1, char const *s2, char const *s3);
void    ft_close_all(t_pip pip);
char *ft_tab_to_str(char **tab, char sep);

//SPLIT_LQUOTES
char	**ft_split_lq(char const *s, char *sep);


// int	pipex(int ac, char **av, char **envp);



#endif

// < Makefile cat | cat | cat > oufile > out > outpierre

// Makefile	cat	-e	 out	| 	Bonjour 	|	cat  outile outpierre	out
// 	1		   3 	  2		4		3		4	 3		2.5		2.5	 	2

// << Makefile cat | cat | cat > oufile > out

// Makefile	cat	-e	 out	| 	 pls >> fichier -la	|	cat | cat  | cat outile 	out
// 1.5		  3   	  2		4	  3.3		2   3.3  4	 3	4	3  4  3	  2.5	 	 2


// ls z > a -la c d
// 4, 
// 	1, 2, DUP, 3 
// 4, 
// 	1, 2, DUP, 3
// 4, 
// 	1, 2, DUP, 3 



