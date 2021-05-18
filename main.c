/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshondra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 01:47:02 by jshondra          #+#    #+#             */
/*   Updated: 2021/05/18 01:47:05 by jshondra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mshell.h"

char	**init(char **envp, int k)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = -1;
	while (envp[i])
		i++;
	new = malloc((i + 1 + k) * sizeof(char *));
	if (!new)
		return (NULL);
	new[i + k] = NULL;
	while (++j < i)
		new[j] = ft_strdup(envp[j]);
	return (new);
}

void	path_init(t_all *all, char **envp)
{
	char	*str;
	char	*term_name;
	int		i;

	i = -1;
	g_exit_status[0] = 0;
	all->env = init(envp, 0);
	term_name = "xterm-256color";
	all->data = NULL;
	all->commands_hist = NULL;
	all->size = 0;
	all->amount = 0;
	all->flag = 0;
	get_env_value(envp, "HOME");
	all->home_path = ft_strdup(get_env_value(envp, "HOME"));
	tgetent(0, term_name);
	str = get_env_value(envp, "OLDPWD");
	if (str[0] == 0)
	{
		parse("export OLDPWD", all);
		all->flag = -1;	
	}
}

void	start_minishell(t_all *all, struct termios term, \
struct termios term1)
{
	char	*input;

	input = NULL;
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &term);
	write(2, "\033[36;1mminishell$\033[0m ", 23);
	tputs(save_cursor, 1, ft_putchar);
	input = select_cap(all, input, term, term1);
	term = term1;
	all->size = all->amount;
	tcsetattr(0, TCSANOW, &term);
	input = add_char(input, '\0');
	create_history(all, input);
	if (ft_strchr(input, '$'))
		all->dola = 1;
	parse(input, all);
	if (input != NULL)
		free(input);
	input = NULL;
	clear_all(&all->data);
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	struct termios	term1;
	t_all			*all;

	(void)argc;
	(void)argv;
	all = NULL;
	all = (t_all *)malloc(sizeof(t_all));
	if (!all)
		return (1);
	path_init(all, envp);
	tcgetattr(0, &term);
	tcgetattr(0, &term1);
	 while (1)
		start_minishell(all, term, term1);
	write(1, "\n", 1);
	close(all->fd);
	return (0);
}
