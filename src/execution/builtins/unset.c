/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:37 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/07 16:26:38 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	builtin_unset(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->argv[i])
	{
		if (is_in_env(cmd->argv[i]))
			g_data.environ = remove_from_env(g_data.environ, cmd->argv[i]);
		if (!g_data.environ)
			ft_exit(EXIT_FAILURE);
		i++;
	}
	return (g_data.exit_status = 0, true);
}
