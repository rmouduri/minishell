/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:20:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/11/23 11:27:42 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <sys/types.h>
# include <stdio.h>

# define NONE 0b0
# define REDIRECT_TO 0b1
# define REDIRECT_FROM 0b10
# define WRITE_TO 0b100
# define READ_FROM 0b1000
# define HERE_DOC 0b10000

# define OPEN_APPEND 1089
# define OPEN_TRUNC 577
# define GIVE_RIGHTS 0664

# define STDIN 0
# define STDOUT 1
# define FDIN 2
# define FDOUT 3

typedef struct s_env {
	char			*name;
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_shell {
	char			**input;
	struct s_env	*env;
	char			**char_env;
	char			**fct;
	char			*exec;
	__int8_t		*ops;
	int				fds[4];
	int				waitstatus;
	char			op;
	int				ret;
	int				pipes;
	int				index;
	int				here_line;
	int				here_fd;
	int				pid_index;
	__pid_t			*cpids;
}	t_shell;

typedef struct s_echo {
	int				index;
	int				arg_sz;
	char			*buff;
}	t_echo;

extern t_shell	*g_shell;

char		**get_input(void);
char		**str_to_tab(char *s, t_env *env);

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
int			ft_strlen_c(const char *s, char c);
int			ft_strlen_ischarset(const char *s, const char *charset);
int			ft_strlen_isncharset(const char *s, const char *charset);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putnbr_fd(int nb, int fd);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strdupncpy(char *s, int len, char *ex, char c);
char		*ft_strdup(char const *src);
int			is_charset(char c, const char *charset);
void		*ft_calloc(void **ptr, int size);
char		*concatenate_str(char *s, char c);
int			free_tab(char **tab, int limit);
char		*get_classic_word(char **ret, char *s, int *i, char *charset);
char		*get_quote(char **ret, char *s, int *i, char c);
char		*get_dollar(char **ret, char *s, int *i);
void		ft_putstr(char *str);
char		*get_same_char(char **ret, char *s, int *i, char c);
int			quote_check(char *arg, int index);
int			go_to_function(int i, int fd);
t_env		*init_env(char **env);
t_env		*ft_envnew(char *s);
char		*get_env_var(char *s);
int			free_env(t_env *env);
char		*init_env_name(char *s);
char		*init_env_var(char *s);
void		free_node(t_env *node);
int			print_env(t_env *env);
char		**free_char_env(char **env, int i);
char		*normal_word(char *s, int *index, int start);
char		**dup_env(void);
void		*free_items(void **item_1, int size_1, void **item_2, int size_2);
char		**get_arg_tab(char **input, int j, int *fd);
int			get_amt_wd_1(char *s, int words, char c);
int			return_error(char *s1, char *s2, char *s3, int ret);
int			check_symbol(char **input, int i);
int			wait_kill_pids(void);
char		*replace_env_var(char *str);
__pid_t		*init_cpids(int amt);
char		*env_input(char *name, char str[256]);
char		*select_env_var(char *s, char str[256]);
char		*get_var_name(char *s, char name[256]);

int			check_function(int i);
int			check_builtins(int i, int *pipefd);
int			check_exec(char **path);
int			open_file(char *path, char *op, int fd);

int			ft_echo(char **arg);
char		*check_quote_dollar(char *s, t_env *env, int keep);
char		*ft_itoa(int nb);

void		sighandler(int signum);

int			init_shell(char **env);
int			free_shell(void);

int			check_args(t_shell *shell, char **av);
char		**get_path(char *name);
int			free_path_tab(char **tab, int i);

int			get_and_open_file(char **input, int i, int *pipefd);
int			ft_redirect(int *pipefd);
int			fork_and_exec(int *pipefd, int i);
void		reset_redirect(void);

void		ft_exit(int *pipefd);
int			ft_cd(void);

int			*create_pipes(void);
int			close_pipes(int *pipefd);

t_env		*create_env_node(char *name, char *var);
void		del_env_node(t_env *env, char *name);

int			dup_close_set(int fd1, int fd2, int val);
int			is_builtin(int i);

void		add_to_env(t_env *node);
t_env		*ft_setenv(char *name, char *var);
t_env		*get_env_node(char *s);

int			ft_unset(void);
int			ft_pwd(void);
int			ft_export(void);
void		print_env_export(char **env);

int			here_doc(int *pipefd, char *heredoc);

char		**str_to_tab_1(char *s);
__int8_t	get_ops(char *s);

#endif
