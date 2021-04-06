/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgordon <rgordon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 19:35:10 by rgordon           #+#    #+#             */
/*   Updated: 2021/04/06 15:42:29 by rgordon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H
#include <term.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

##dgfdgfdg
typedef struct	s_args
{
	char	*bin;
	char    **args;
}				t_args;
typedef struct	s_data
{
	t_args			*arg;
	struct s_data	*next;
}				t_data;

void	parse(char *input, char **envp);

#endif
