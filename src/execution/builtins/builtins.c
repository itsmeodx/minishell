/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:38:03 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/17 19:38:03 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool	is_builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->argv[0], "echo") || !strcmp(cmd->argv[0], "cd")
		|| !strcmp(cmd->argv[0], "pwd") || !strcmp(cmd->argv[0], "export")
		|| !strcmp(cmd->argv[0], "exit"))
		return (true);
	return (false);
}

int	execute_builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->argv[0], "echo"))
		return (!builtin_echo(cmd));
	if (!strcmp(cmd->argv[0], "cd"))
		return (!builtin_cd(cmd));
	if (!strcmp(cmd->argv[0], "pwd"))
		return (!builtin_pwd());
	if (!strcmp(cmd->argv[0], "export"))
		return (!builtin_export(cmd));
	if (!strcmp(cmd->argv[0], "exit"))
		return (!builtin_exit(cmd));
	return (EXIT_FAILURE);
}
