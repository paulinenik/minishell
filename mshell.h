/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:35:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/04/13 17:26:07 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <stdio.h>

typedef struct	s_data
{
	char			*bin;
	char    		**args;
	struct s_data	*next;
	
	
}				t_data;

typedef struct	s_all
{
	t_data			*data;
	char			**env;
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

void    get_pwd(t_all *all);
void    get_export(t_all *all);
char	**init(char **envp, int k);
char	*delete_char(char *str);
void    get_env(t_all *all);
void	get_cd(t_all *all);
void	td_array_clear(char **arr);
<<<<<<< HEAD
void	clear_all(char **input, t_data *data);
void	get_echo(t_all *all);
=======
void	clear_all(t_data **data);
>>>>>>> fadbb6c60ac6e74433969ace42089f08f578dc7d

#endif
