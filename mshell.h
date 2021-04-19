/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:35:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/04/19 18:59:56 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
typedef struct	s_data
{
	char			*bin;
	char    		**args;
	struct s_data	*next;
	int				*fd;
	int				*old_fd;
	
	
}				t_data;

typedef struct	s_all
{
	t_data			*data;
	char			**env;
	char			home_path[100];
	char			*old_pwd;
	char			**commands_hist;
	int				size;
	int 			fd;
}				t_all;

void	parse(char *input, t_all *all);
t_data	*init_data(void);
char	*add_char(char *str, char c);
char	*init_exec_name(char **input, char **envp);
char	*single_qoutation(char **input, char *arg);
char	*double_quotation(char **input, char **envp, char *arg);
char	*get_envp(char **input, char **envp, char *arg);
char 	*get_var_value(char **envp, char *key);
int		ft_putchar(int c);
char	**get_args(char **input, char **envp);
char	**list_to_array(t_list *list);
void	check_specchar(char **input, t_all *all);
void	add_data_front(t_data **old, t_data *new);
void	revert_data(t_data **data);
int		data_size(t_data *data);

int    get_pwd(t_all *all);
int    get_export(t_all *all);
char	**init(char **envp, int k);
char	*delete_char(char *str);
int    get_env(t_all *all);
int	get_cd(t_all *all);
void	td_array_clear(char **arr);
int	get_echo(t_all *all);
void	clear_all(t_data **data);
int    get_unset(t_all *all);

int	*init_fd(void);
void	redirect_parse(char **input, t_all *all);
void	redirect_append(char **input, t_all *all);
void	redirect_write(char **input, t_all *all);
void	redirect_read(char **input, t_all *all);
void	change_fd(t_data *data);
void	return_fd(t_data *data);

void	to_process(t_all *all);
int exec_cmd(t_all * all);
char *check_path(char *filename, char *path);

#endif
