/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:37 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/07 11:48:37 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
char	**remove_from_env(char **env, char *key)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	i = 0;
	j = 0;
	len = strlen(key);
	while (env && env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		if (strncmp(env[i], key, len) != 0)
			new_env[j++] = env[i];
		else
			free(env[i]);
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}

bool	builtin_unset(t_cmd *cmd)
{
	int		i;
	char	*key;

	i = 1;
	while (cmd->argv[i])
	{
		key = ft_strjoin(cmd->argv[i], "=");
		if (is_in_env(key))
			g_data.environ = remove_from_env(g_data.environ, key);
		if (!g_data.environ)
			ft_exit(EXIT_FAILURE);
		free(key);
		i++;
	}
	return (g_data.exit_status = 0, true);
}
