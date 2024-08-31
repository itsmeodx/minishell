/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:21:46 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/31 17:33:31 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*ft_getenv(char *name)
{
	int		i;

	i = 0;
	while (g_data.environ && g_data.environ[i])
	{
		if (strncmp(g_data.environ[i], name, strlen(name)) == 0)
			return (g_data.environ[i] + strlen(name) + 1);
		i++;
	}
	return (NULL);
}

char	**addtoenv(char **env, char *key, char *value)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	key = ft_strjoin(key, "=");
	new_env[i] = ft_strjoin(key, value);
	free(key);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

void	check_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (!path)
	{
		g_data.environ = addtoenv(g_data.environ, "PATH", PATH);
		if (!g_data.environ)
			ft_exit(EXIT_FAILURE);
	}
}

void	update_pwd(char **env)
{
	char	*pwd;

	update_env(env, "OLDPWD", getenv("PWD"));
	pwd = getcwd(NULL, 0);
	update_env(env, "PWD", pwd);
	free(pwd);
}

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

void	update_env(char **env, char *key, char *value)
{
	int		i;

	key = ft_strjoin(key, "=");
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], key, strlen(key)) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin(key, value);
			break ;
		}
		i++;
	}
	free(key);
}
