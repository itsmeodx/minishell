/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/12 10:55:47 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool	echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (cmd->argc > 1 && !strcmp(cmd->argv[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (i < cmd->argc)
	{
		printf("%s", cmd->argv[i]);
		if (i + 1 < cmd->argc)
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (true);
}
