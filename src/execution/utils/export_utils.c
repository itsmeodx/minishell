/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:09:46 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/11 09:09:46 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
