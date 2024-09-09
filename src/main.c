/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/07 10:17:57 by oouaadic         ###   ########.fr       */
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
	while (true)
	{
		g_data.input = ft_readline(create_full_prompt());
		if (!g_data.input)
			break ;
		g_data.tree = ft_parsing(g_data.input);
		if (g_data.tree)
			ft_execution(g_data.tree);
		ft_treeclear(g_data.tree);
	}
	free_2d(g_data.environ);
	rl_clear_history();
	close(g_data.hfd);
	free(g_data.home);
	printf("exit\n");
	return (g_data.exit_status);
}
