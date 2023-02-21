/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngriveau <ngriveau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:01:03 by pbizien           #+#    #+#             */
/*   Updated: 2023/02/21 18:00:30 by ngriveau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>	
# include <stdlib.h>
# include <limits.h>
# include "get_next_line_p.h"

typedef struct s_data
{
	int		pipefd2[2];
	int		pipefd1[2];
	int		fd_in;
	int		fd_out;
	char	**paths;
	int		npath1;
	int		npath2;
	char	**param1;
	int		last_pid;
	char	**av;
	char	**envp;
	int		ac;
	char	*limiter;
	int		tmp_fd;
	int		hd;
}				t_data;

//MAIN
char	**ft_get_paths(char **envp);
char	**ft_put_bs(char **paths);
int		ft_find_g_path(t_data *data, char **param, int n);
int		ft_size_dchar(char **strstr);
int		pipex(int ac, char **av, char **envp);

//CLOSE
void	ft_close_all(t_data *data);
void	ft_close(int *fd);
void	ft_free_dchar(char **str);
void	ft_finish_f1(t_data *data, char **av);
void	ft_finish_f1_bis(t_data *data);

//CLOSE 2
void	ft_finish_lf(t_data *data, char **av, int i);
void	ft_finish_lf_bis(t_data *data);
int		ft_end(t_data *data);
void	ft_not_found(char *str);
void	ft_no_dir(char *str);

//CLOSE 3
void	ft_close_if(int *fd, t_data *data);
void	ft_exec(t_data *data);

//UTILS
int		ft_init(char **av, t_data *data, char**envp, int ac);
void	ft_not_found(char *str);
void	ft_no_dir(char *str);
void	ft_first_child(t_data *data, char **av, char **envp);
void	ft_last_child(t_data *data, char **av, char **envp, int i);
int		ft_main_suite(t_data *data, char **av, char **envp);

//UTILS 2
int		ft_middle(t_data *data);

//HEREDOC
int		ft_heredoc(t_data *data);
void	ft_init_pipe(t_data *data);

void	ft_print_fds(t_data *data);

//FILES LIBFT
long	ft_p_atoi(const char *nptr);
void	*ft_p_calloc(size_t nmemb, size_t size);
int		ft_p_isdigit(int c);
void	ft_p_putendl_fd(char *s, int fd);
char	**ft_p_split(char const *s, char c);
char	*ft_p_strdup(const char *s);
char	*ft_p_strjoin(char const *s1, char const *s2);
size_t	ft_p_strlen(const char *s);
int		ft_p_strncmp(const char *s1, const char *s2, size_t n);
void	ft_p_bzero(void *s, size_t n);
void	ft_p_putstr_fd(char *s, int fd);
void	*ft_p_memcpy(void *dest, const void *src, size_t n);
void	*ft_p_memset(void *b, int c, size_t len);





#endif