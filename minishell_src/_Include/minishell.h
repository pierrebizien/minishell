
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
#define MAL_ERCODE -42
#define M_C_RW O_CREAT | O_RDWR


#define F_INFILE 0
#define F_DELIMITER 1
#define F_DELIMITER_SQ 4

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

typedef	struct	s_split
{
	size_t			count;
	size_t			index;
	size_t			i;
	int				sq;
	int				dq;

}               t_split;

typedef	struct	s_to_free
{
	char 			*str;
	char 			*cpy_str_tty;
	char 			**env_tab;
	char 			**paths_env;
	char			*path_exec;
	char			**cmd;
	char			**cmd_quotes;
	int				w;
	int				hd_break;

	
}               t_to_free;

typedef struct	s_exec
{
	char			*str;
	int				id;
	char			*quotes;
	char			*hd_filename;
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
	int		saved_stdin;
	int		saved_stdout;
	int		pipefd1[2];
	int		pipefd2[2];
}				t_pip;


typedef	struct	s_data
{
	t_env	env;
	t_exec	exec;
	t_pip	pip;
	t_to_free to_free;
    char 	**args;
	int		ac;
	char 	**av;
	char	**envp;
	char	*sep;
	int		hd;
	int		bool_redir_0;
	int		bool_redir_2;
	char	*pwd;
	char	*oldpwd;
	int		err_built_in;
	int		last_err_num;
	char	*cpy_str_tty;
	
}               t_data;


//FT_PARSING
int	ft_parse_for_exec(t_data *data);
char	*ft_parse(char *str, t_data *data);
int		is_ws(char c);
char	*ft_check_env(char *str, t_data *data);
size_t	ft_strlen_ws_quotes(const char *str);
char	*ft_convert_variable(char *str, t_data *data);
char	*ft_convert_variable_hd(char *str, t_data *data, char *delimiter);
char	*ft_clean(char *str, t_data *data);
void	ft_free_dchar(char **str);
void	ft_print_list(t_exec *begin);
void	ft_clean_ws(t_data *data);
size_t	ft_strlen_var_env(char *str);
char	*ft_check_env(char *str, t_data *data);
int	ft_is_hd(char *str, int	i);
int	ft_count_pipes (t_exec *begin);
char ft_first_no_chev(char *str);
int ft_verif_et_ou(char *str);
t_exec	*ft_lstnew_pars(void);
int ft_check_chev_pip(char **tab);
int	ft_check_if_past_is_delim(t_exec *begin, int i);
int	ft_find_if_hd_quotes(t_data *data, int count_p);
char	*ft_clean_quotes(char *str);
void ft_clean_list_exec(t_data *data);
int ft_modif_in_out(t_data *data);
void ft_mod_in_out_bis_2(t_exec **tmp, int *bool_in);
void ft_mod_in_out_bis(t_exec **tmp, int *bool_out, int *bool_in);
int ft_falsed(t_data *data, t_exec **tmp, int *ret_val);
int ft_delimiter(t_data *data, t_exec **tmp, int *ret_val);
int ft_delimiter_sq(t_data *data, t_exec **tmp, int *ret_val);
int ft_verif_pipe(char *str);
int ft_verif_just_chev(char *str);
// char	*ft_clean(char *str, t_data *data);




void	ft_pb_malloc(t_data *data);
void	ft_free_list(t_exec *begin);
void	ft_free_err_mal_cmd_solo(char **cmd, char **cmd_quotes, t_data *data);


//FT_INIT

int ft_init(char **env, t_data *data);

//FT_ENV 42
int		ft_create_env(char **envp, t_data *data);
t_env	*ft_lstnew_env(void);
void	ft_free_env(t_data *data);
int		ft_env(char **cmd, t_data *data);



//FT_UNSET
int		ft_unset(char **strr, t_data *data);

//FT_EXPORT
int		ft_export(char **tab, t_data *data, char **cmd_quotes);
size_t	ft_strlen_ws(const char *str);
int		ft_just_export(t_data *data);
int		ft_verif_str_export(char *str);
int		ft_verif_option_export(char **cmd, char **cmd_quotes);
void	ft_export_putstr(char *cmd);


// FT_ECHO
int		ft_echo(char **cmd, char **cmd_quotes);

// FT_PWD
int		ft_pwd(char **cmd, t_data *data);

// FT_CD
int		ft_cd(char **str, t_data *data);

// FT_EXIT
int		ft_exit(char **cmd, t_data *data, char **cmd_quotes);

//FT_TEST_BUILDTIN
int		ft_test_builtin(char **str);
int		ft_exec_builtin(char **cmd, t_data *data, char **cmd_quotes);



void	ft_ctrlb(int a);
void	ft_ctrlb_exec(int a);
void	ft_ctrlc_exec(int a);
void	ft_ctrlc_hd(int a);

int event(void);

void	ft_ctrlc(int a);


// Split_keep

void	free_tabstr_2(char **tab);
int		set_mem_2_if(char **tab, char const *s, char *sep, t_split	*split);
int		set_mem_2_else(char **tab, char const *s, t_split	*split);
int		set_mem_2(char **tab, char const *s, char *sep, t_split	*split);
char	**ft_split_k(char const *s, char *sep);
//1
void	fill_tab_2(char *new, char const *s, char *sep);
int	is_sep(char c, char *sep);
size_t	count_words_2(char const *s, char *sep);



// Split_leave
size_t	count_words_3(char const *s, char *sep);
void	fill_tab_3(char *new, char const *s, char *sep);
void	free_tabstr_3(char **tab);
int		set_mem_3(char **tab, char const *s, char *sep);
char	**ft_split_l(char const *s, char *sep);
//1
int	is_sep_3(char c, char *sep);

//FT_STRTRIM_LQ
char	*ft_strtrim_lq(char const *s1);

//FT_FREE
void	ft_print_dargs(char **strstr);
void	ft_unlink_hd(t_exec *begin);
void ft_free_end(t_data *data);


int	ft_in_q(int in_q);

//FT_PIPEX



//FT_UTILS
int		ft_strstrlen(char **strstr);
size_t	ft_strlen_WS(const char *str);
char	*ft_put_str_in_str(char *dest, char *src, int ind);
void	ft_maj_quotes(int *dq, int *sq, char c);
void	ft_close(int *fd);


//FT_HEREDOC
void	ft_heredoc_end(t_data *data, char *delimiter, int w, char *str);
char	*ft_heredoc_init_var(t_data *data, int w);
int		ft_heredoc_maxi_while(char **str, t_data *data, char *delimiter, int sq);
char	*ft_heredoc(t_data *data, char *delimiter, int w, int sq);
void	ft_init_pipex_pipe(t_data *data);

//1
void	ft_manage_write(char *str, char *delimiter, t_data *data, int sq);
int		ft_heredoc_if_w(char **name, t_data *data);
char	*ft_heredoc_prompt(char *str, t_data *data);


//PIPEX_UTILS
char    *ft_strrjoin(char const *s1, char const *s2, char const *s3);
void    ft_close_all(t_pip pip, t_data *data);

//SPLIT_LQUOTES
void	free_tabstr_4(char **tab);
int	set_mem_4_if(char **tab, char const *s, t_split *split);
void	set_mem_4_while(char const *s, char *sep, t_split	*split);
int	set_mem_4(char **tab, char const *s, char *sep, t_split	*split);
char	**ft_split_lq(char const *s, char *sep);
//1
int	is_sep_4(char c, char *sep);
size_t	count_words_4(char const *s, char *sep);
void	fill_tab_4(char *new, char const *s, int len);


//FT_EXEC_BUILT_IN
void	ft_free_err_mal_cmd_solo(char **cmd, char **cmd_quotes, t_data *data);
int		ft_exec_cmd_solo(t_data *data, char **cmd, char **cmd_quotes);
void	ft_free_child_exec_solo(t_data *data, char **cmd, char **cmd_quotes);
int		ft_exec_built_in_solo_test_builtin(t_exec *begin, t_data *data, int *rt_val);
int		
ft_exec_built_in_solo(t_exec *begin, t_data *data);
//1
int		ft_ebs_falsin(t_exec *begin, t_data *data);
int		ft_ebs_fasea(t_exec *begin, t_data *data);
int		ft_ebs_faset(t_exec *begin, t_data *data);
int		ft_ebs_append(t_exec *begin, t_data *data);
int		ft_ebs_tronc(t_exec *begin, t_data *data);
//2
int		ft_ebs_infile(t_exec *begin, t_data *data);
int		ft_exec_built_in_solo_finish(t_data *data);
// int	pipex(int ac, char **av, char **envp);

// MAIN
void	ft_init_sigint_exec(void);
void	ft_init_sigquit_exec(void);
void	ft_init_sigquit(void);
void	ft_init_sigint(void);
void	ft_init_sigint_hd(void);


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



