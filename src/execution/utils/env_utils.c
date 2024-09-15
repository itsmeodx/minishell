/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:58:41 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/07 19:58:41 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*get_home(void)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid < 0)
		return (close_pipe(fd), NULL);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		execve("/usr/bin/bash", (char *[]){"bash", "-c", "echo ~", NULL},
			NULL);
		ft_exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		free(g_data.home);
		g_data.home = get_next_line(fd[0]);
		g_data.home[strlen(g_data.home) - 1] = '\0';
	}
	return (close_pipe(fd), g_data.home);
}

char	**var_split(char *var)
{
	int		i;
	char	**key_value;

	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '+')
		i++;
	if (var[i] == '+' && var[i + 1] == '=')
		i++;
	key_value = malloc(sizeof(char *) * 3);
	if (!key_value)
		return (NULL);
	key_value = memset(key_value, 0, sizeof(char *) * 3);
	key_value[0] = ft_substr(var, 0, i + 1 - (var[i] == '=')
			- (i - 1 >= 0 && var[i - 1] == '+'));
	if (var[i] == '=')
		key_value[1] = ft_strdup(var + i + 1);
	return (key_value);
}

bool	is_valid_key(char *key, bool *bad_key)
{
	int		i;
	bool	ret;
	char	**key_value;

	if (!bad_key)
		bad_key = &ret;
	key_value = var_split(key);
	if (!key_value)
		return (*bad_key = true, false);
	if ((!isalpha(*key_value[0]) && *key_value[0] != '_') || !*key_value[0])
		return (dprintf(STDERR_FILENO,
				NAME "export: `%s': " NVI "\n", key), *bad_key = true,
			free_2d(key_value), false);
	i = -1;
	while (key_value[0][++i])
	{
		if (!isalnum(key_value[0][i]) && key_value[0][i] != '_')
			return (dprintf(STDERR_FILENO,
					NAME "export: `%s': " NVI "\n", key), *bad_key = true,
				free_2d(key_value), false);
	}
	return (free_2d(key_value), *bad_key = false, true);
}

char	**remove_from_env(char **env, char *key)
{
	int		i[2];
	int		len;
	char	**new_env;

	i[0] = 0;
	i[1] = 0;
	len = strlen(key);
	while (env && env[i[0]])
		i[0]++;
	new_env = malloc(sizeof(char *) * (i[0]));
	if (!new_env)
		return (free(env), NULL);
	i[0] = -1;
	while (env && env[++i[0]])
	{
		if (strncmp(env[i[0]], key, len) == 0 && (env[i[0]][len] == '='
			|| env[i[0]][len] == '\0'))
			free(env[i[0]]);
		else
			new_env[i[1]++] = env[i[0]];
	}
	new_env[i[1]] = NULL;
	free(env);
	return (new_env);
}

char	**filter_env(char **env)
{
	int		i;
	char	**key_value;

	i = -1;
	while (env && env[++i])
	{
		if (!strchr(env[i], '='))
		{
			key_value = var_split(env[i]);
			env = remove_from_env(env, key_value[0]);
			free_2d(key_value);
			i--;
		}
	}
	return (env);
}
