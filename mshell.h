/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:35:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/04/09 22:21:19 by rgordon          ###   ########.fr       */
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
	// char			**env;
	struct s_data	*next;
	char			**new;
	
}				t_data;

typedef struct	s_all
{
	char			**env;
	char			*test;
}				t_all;

void	parse(char *input, char **envp);
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
void	check_specchar(char **input, char **envp, t_data *data);

void    get_pwd(t_data *data);
void    get_export(t_data *data);
char	**init(char **envp, int k);
char	*delete_char(char *str);

#endif
