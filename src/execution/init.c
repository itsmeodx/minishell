/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:38:50 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 12:50:56 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
void	update_shlvl(char **env)
{
	int		i;
	char	*shlvl;
	int		lvl;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL=")) == 0)
		{
			lvl = ft_atoi(env[i] + ft_strlen("SHLVL="));
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

	path = ft_getenv("PATH", env);
	if (!path)
	{
		g_data()->environ = addtoenv(env, "PATH", PATH);
		if (!g_data()->environ)
			ft_exit(EXIT_FAILURE);
	}
}

static
void	check_pwd(char **env)
{
	char	*pwd;

	pwd = ft_getenv("PWD", env);
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return ;
		g_data()->environ = addtoenv(env, "PWD", pwd);
		free(pwd);
		if (!g_data()->environ)
			ft_exit(EXIT_FAILURE);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (ft_strcmp(pwd, ft_getenv("PWD", env)) != 0)
			update_env(env, "PWD", pwd);
		free(pwd);
	}
}

void	init_minishell(char **env)
{
	*g_data() = (struct s_data){0};
	g_data()->environ = ft_strdup_2d(env);
	if (!g_data()->environ)
	{
		g_data()->environ = malloc(sizeof(char *));
		if (!g_data()->environ)
			ft_exit(EXIT_FAILURE);
		g_data()->environ[0] = NULL;
	}
	check_path(g_data()->environ);
	g_data()->home = get_home();
	if (!is_in_env("HOME", g_data()->environ))
		g_data()->environ = addtoenv(g_data()->environ, "HOME", g_data()->home);
	update_shlvl(g_data()->environ);
	check_pwd(g_data()->environ);
	set_hostname(g_data()->environ);
	restore_history();
}
