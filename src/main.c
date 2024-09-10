/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/10 18:42:38 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

// global variable
struct s_data	g_data;

static
void	update_shlvl(char **env)
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

static
void	check_path(char **env)
{
	char	*path;

	path = ft_getenv("PATH");
	if (!path)
	{
		g_data.environ = addtoenv(env, "PATH", PATH);
		if (!g_data.environ)
			ft_exit(EXIT_FAILURE);
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
	set_hostname(g_data.environ);
}

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
		if (g_data.tree)
			ft_execution(g_data.tree);
		ft_treeclear(g_data.tree);
	}
	free_2d(g_data.environ);
	rl_clear_history();
	close(g_data.hfd);
	printf("exit\n");
	return (EXIT_SUCCESS);
}
