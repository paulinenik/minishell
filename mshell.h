#ifndef MSHELL_H
# define MSHELL_H
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <termios.h>
# include <string.h>
# include <signal.h>

typedef struct s_data
{
	char			*bin;
	char			**args;
	struct s_data	*next;
	int				*fd;
	int				*old_fd;
}				t_data;

typedef struct s_all
{
	t_data			*data;
	char			**env;
	char			*home_path;
	char			*old_pwd;
	char			**commands_hist;
	int				size;
	int				len_env;
	int				fd;
	int				operators_flag;
	int				amount;
	int				dola;
	int				flag;
	int				shlvl;
}				t_all;

int		g_exit_status[2];
void	parse(char *input, t_all *all);
t_data	*init_data(void);
char	*add_char(char *str, char c);
char	*init_exec_name(char **input, char **envp);
char	*single_qoutation(char **input, char *arg);
char	*double_quotation(char **input, char **envp, char *arg);
char	*parse_dollar(char **input, char **envp, char *arg);
char	*get_env_value(char **envp, char *key);
int		ft_putchar(int c);
char	**get_args(char **input, char **envp);
char	**list_to_array(t_list *list);
void	check_specchar(char **input, t_all *all);
void	add_data_front(t_data **old, t_data *new);
void	revert_data(t_data **data);
int		data_size(t_data *data);

int		get_pwd(void);
int		get_export(t_all *all);
char	**init(char **envp, int k);
char	*delete_char(char *str);
int		get_env(t_all *all);
int		get_cd(t_all *all);
void	td_array_clear(char **arr);
int		get_echo(t_all *all);
void	clear_data(t_data **data);
int		get_unset(t_all *all);
void	print_export(t_all *all, int i, int j);
char	**alph_sort(char **copy, int n);
void	check_export(t_all *all, int i, int j, int len);
int		check_for_value(t_all *all, int i, int k);
int		save_index(t_data *data, char **envp);
int		alnum_search(char **str, int i, int temp, int s);
char	**unseter(t_all *all, int i, int j, char **copy);
int		get_exit(t_all *all);
void	check_dir(char	*str, t_all *all);
int		alnum_search(char **str, int i, int temp, int s);
void	free_copy(char **copy, int i);
char	*move_left(char *input, int *i);
char	*move_right(char *input, int *i);
char	*delete_symbol(char *input, int *i);
char	*control_c(char *input, char buf[101]);
void	ctrl_d(struct	termios	term, struct termios term1, char *input);
char	*usual_cap(char *input, int *i, char buf[101]);
char	*arrow_down(char *input, t_all *all, int *i, int l);
char	*arrow_up(char *input, t_all *all, int *i, int l);
char	*select_cap(t_all *all, char *input, struct termios term, \
struct termios term1);
void	create_history(t_all *all, char *str);
char	*delete_symbol(char *input, int *i);
char	*arrow_down(char *input, t_all *all, int *i, int l);
char	*arrow_up(char *input, t_all *all, int *i, int l);
void	print_env(t_all *all, int i);
void	dir_back(t_all *all);
void	ft_signal_cltr_c(int sig);
void	sigint2(int num);
void	sigquit2(int num);
void	sigquit(int num);
void	sigint(int num);
void	exit_code(t_all *all);
void	set_shlvl(t_all *all);
void	catch_sig(t_all *all);
void	help_dir(int i, char *str, t_all *all, char dir[1024]);
void	set_oldpwd(t_all *all);

int		*init_fd(void);
void	redirect_parse(char **input, t_all *all);
void	redirect_append(char **input, t_all *all);
void	redirect_write(char **input, t_all *all);
void	redirect_read(char **input, t_all *all);
void	change_fd(t_data *data);
void	return_fd(t_data *data);

void	to_process(t_all *all);
int		exec_cmd(t_all *all);
void	check_for_directory(t_all *all);
char	*check_path(char *filename, char *path);

int		array_size(char **arr);
char	**array_add_front(char **arr, char *str);

char	*null_strjoin(char const *s1, char const *s2);
void	array_concat(t_data *data, char **new_args);

void	create_child_process(char *path, t_all *all);
void	init_cwd_argv(t_all *all);
int		exec_builtin(t_all *all);
char	*get_path(t_all *all);
char	*search_bin(char *filename, char **path_list);
char	*get_exit_status(char **input, char *arg);
char	*get_env_key(char **input);
void	parse_semicolon(char **input, t_all *all);
int		parse_pipes(char **input, t_all *all);
void	stop_parse(char **input, int error_code);
void	toggle_operator_flag(char **input, t_all *all);

#endif
