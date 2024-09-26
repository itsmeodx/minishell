/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/26 16:15:51 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

// global variable
struct s_data	g_data;

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
			char **env)
{
	init_minishell(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while (true)
	{
		signal(SIGINT, ft_signal);
		g_data.input = ft_readline(create_full_prompt());
		if (!g_data.input)
			break ;
		g_data.tree = ft_parsing(g_data.input);
		if (!g_data.tree)
			continue ;
		ft_execution(g_data.tree);
		ft_treeclear(g_data.tree);
		g_data.tree = NULL;
		if (g_data.exit_status == SIGINT + 128)
			ft_printf("\n");
		else if (g_data.exit_status == SIGQUIT + 128)
			ft_printf("Quit (core dumped)\n");
	}
	ft_printf("exit\n");
	ft_exit(g_data.exit_status);
}
