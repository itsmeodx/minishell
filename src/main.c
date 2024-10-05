/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/10/05 12:31:46 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

/*
** global variable
*/
struct s_data	*g_data(void)
{
	static t_data	data;

	return (&data);
}

void	*ft_semicolon(char *input)
{
	char	**split_input;
	int		len;
	t_tree	**ptr;
	int		i;

	split_input = ft_qsplit(input, ";");
	i = 0;
	len = ft_strlen_2d(split_input);
	ptr = malloc(sizeof(t_tree) * (len + 1));
	if (!ptr)
		return (NULL);
	while(split_input[i])
	{
	 	ptr[i] = ft_parsing(split_input[i]);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
			char **env)
{
	int	i;

	init_minishell(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while (true)
	{
		signal(SIGINT, ft_signal);
		g_data()->input = ft_readline(create_full_prompt());
		if (!g_data()->input)
			break ;
		g_data()->trees = ft_semicolon(g_data()->input);
		if (!g_data()->trees || !*g_data()->trees)
			continue ;
		i = -1;
		while (g_data()->trees[++i])
			ft_execution(g_data()->trees[i]);
		ft_treesclear(g_data()->trees);
		g_data()->trees = NULL;
	}
	ft_printf("exit\n");
	ft_exit(g_data()->exit_status);
}
