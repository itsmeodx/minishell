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

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

bool	print_export(char **env)
{
	int		i;
	int		j;
	char	**environ;

	environ = ft_strdup_2d(env);
	sort_env(environ);
	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && environ[i][j] != '=')
			j++;
		printf("declare -x %.*s=\"%s\"\n", j, environ[i], environ[i] + j + 1);
		i++;
	}
	free_2d(environ);
	return (true);
}

bool	builtin_export(t_cmd *cmd)
{
	char	**env;

	env = __environ;
	if (cmd->argc == 1)
		return (print_export(env));
	return (true);
}
