/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:12:05 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 21:39:48 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	builtin_unalias(t_cmd *cmd)
{
	int		i;
	bool	bad_key;

	if (cmd->argc == 1)
		return (ft_dprintf(STDERR_FILENO, "unalias: usage: unalias "
				"name [name ...]\n"), g_data()->exit_status = 2, false);
	if (cmd->argc == 2 && ft_strcmp(cmd->argv[1], "-a") == 0)
		return (free_2d(g_data()->aliases), g_data()->aliases = NULL,
			g_data()->exit_status = 0, true);
	i = 0;
	bad_key = false;
	while (cmd->argv && cmd->argv[++i])
	{
		if (!is_in_env(cmd->argv[i], g_data()->aliases))
		{
			ft_dprintf(STDERR_FILENO, "unalias: %s: not found\n", cmd->argv[i]);
			bad_key = true;
		}
		else
			g_data()->aliases = remove_from_env(g_data()->aliases,
				cmd->argv[i]);
	}
	return (g_data()->exit_status = bad_key, true);
}
