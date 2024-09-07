/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:09:50 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/27 15:09:50 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		j = i;
		while (env[++j])
		{
			if (strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
		}
	}
}

static
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
	key_value[0] = strndup(var, i);
	key_value[1] = strdup(var + i + (1 * (var[i] == '=')));
	if (!key_value[0] || !key_value[1])
		return (free_2d(key_value), NULL);
	if (*key_value[1] == '\0')
	{
		free(key_value[1]);
		key_value[1] = NULL;
	}
	key_value[2] = NULL;
	return (key_value);
}

static
bool	print_export(char **env)
{
	int		i;
	char	**key_value;

	env = ft_strdup_2d(env);
	sort_env(env);
	i = -1;
	while (env[++i])
	{
		key_value = var_split(env[i]);
		if (!key_value)
			return (free_2d(env), false);
		printf("declare -x %s", key_value[0]);
		if (key_value[1])
			printf("=\"%s\"", key_value[1]);
		printf("\n");
		free_2d(key_value);
	}
	free_2d(env);
	return (true);
}

bool	builtin_export(t_cmd *cmd)
{
	int		i;
	char	*key;
	char	**key_value;

	if (cmd->argc == 1)
		return (print_export(g_data.environ));
	i = 0;
	while (cmd->argv[++i])
	{
		key_value = var_split(cmd->argv[1]);
		if (!key_value)
			return (g_data.exit_status = 1, false);
		key = ft_strjoin(key_value[0], "=");
		if (!key)
			return (g_data.exit_status = 1, free(key_value), false);
		if (is_in_env(key))
			update_env(g_data.environ, key_value[0], key_value[1]);
		else
			g_data.environ = addtoenv(g_data.environ, key_value[0],
					key_value[1]);
		free(key);
		free_2d(key_value);
	}
	return (true);
}
