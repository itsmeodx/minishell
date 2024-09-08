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
	char	**key_value;

	if (cmd->argc == 1)
		return (print_export(g_data.environ));
	i = 0;
	while (cmd->argv[++i])
	{
		key_value = var_split(cmd->argv[1]);
		if (!key_value)
			return (g_data.exit_status = 1, false);
		if (is_in_env(key_value[0]))
			update_env(g_data.environ, key_value[0], key_value[1]);
		else
			g_data.environ = addtoenv(g_data.environ, key_value[0],
					key_value[1]);
		free_2d(key_value);
	}
	return (true);
}
