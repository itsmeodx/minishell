/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:21:46 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/27 12:21:46 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

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
