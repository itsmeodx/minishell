/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/31 18:40:21 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

// global variable
struct s_data	g_data;

static void	update_shlvl(char **env)
{
	int		i;
	char	*shlvl;
	int		lvl;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "SHLVL=", strlen("SHLVL=")) == 0)
		{
			lvl = atoi(env[i] + strlen("SHLVL="));
			lvl++;
			shlvl = ft_itoa(lvl);
			free(env[i]);
			env[i] = ft_strjoin("SHLVL=", shlvl);
			free(shlvl);
			break ;
		}
		i++;
	}
}

void	init_minishell(char **env)
{
	g_data = (struct s_data){0};
	restore_history();
	g_data.environ = ft_strdup_2d(env);
	if (!g_data.environ)
	{
		g_data.environ = malloc(sizeof(char *));
		if (!g_data.environ)
			ft_exit(EXIT_FAILURE);
		g_data.environ[0] = NULL;
	}
	update_shlvl(g_data.environ);
	check_path(g_data.environ);
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),
			char **env)
{
	init_minishell(env);
	while (true)
	{
		g_data.prompt = ft_getprompt();
		g_data.input = readline(g_data.prompt);
		free(g_data.prompt);
		if (!g_data.input)
			break ;
		g_data.tree = ft_parsing(g_data.input);
		if (g_data.tree && *g_data.input)
			ft_add_history(g_data.input);
		free(g_data.input);
		if (g_data.tree)
			ft_execution(g_data.tree);
		ft_treeclear(g_data.tree);
	}
	free_2d(g_data.environ);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
