/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/27 12:42:19 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

// global variable
struct s_data	g_data;

void	init_minishell(void)
{
	restore_history();
	g_data.environ = ft_strdup_2d(__environ);
	__environ = g_data.environ;
	update_shlvl(g_data.environ);
//	check_path();
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
			char **env __attribute__((unused)))
{
	init_minishell();
	while (true)
	{
		g_data.prompt = ft_getprompt();
		g_data.input = readline(g_data.prompt);
		__environ = g_data.environ;
		free(g_data.prompt);
		if (!g_data.input)
			break ;
		if (*g_data.input)
			ft_add_history(g_data.input);
		g_data.tree = ft_parsing(g_data.input);
		free(g_data.input);
		if (g_data.tree)
			ft_execution(g_data.tree);
		ft_treeclear(g_data.tree);
	}
	free_2d(g_data.environ);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
