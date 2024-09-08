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

char	**var_split(char *var)
{
	int		i;
	char	**key_value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key_value = malloc(sizeof(char *) * 3);
	if (!key_value)
		return (NULL);
	key_value = memset(key_value, 0, sizeof(char *) * 3);
	key_value[0] = ft_substr(var, 0, i);
	if (var[i] == '=')
		key_value[1] = ft_strdup(var + i + 1);
	return (key_value);
}

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
		if (strncmp(env[i], key, len) != 0
			|| (env[i][len] != '=' && env[i][len] != '\0'))
			new_env[j++] = env[i];
		else
			free(env[i]);
	}
	new_env[j] = NULL;
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
		}
	}
	return (env);
}
