/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:38:03 by oouaadic          #+#    #+#             */
/*   Updated: 2024/10/03 10:58:53 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_builtin(t_cmd *cmd)
{
	int			i;
	static char	*builtins[] = {"alias", "echo", "cd", "pwd", "export",
		"unset", "env", "exit", "unalias", "help", NULL};
	static bool	(*builtin_functions[])(t_cmd *) = {&builtin_alias,
		&builtin_echo, &builtin_cd, &builtin_pwd, &builtin_export,
		&builtin_unset, &builtin_env, &builtin_exit, &builtin_unalias,
		&builtin_help};

	i = -1;
	while (builtins[++i])
	{
		if (cmd && cmd->argv && !ft_strcmp(cmd->argv[0], builtins[i]))
		{
			if (!set_redirections(cmd->redirections))
				return (g_data()->exit_status = 1, EXIT_SUCCESS);
			builtin_functions[i](cmd);
			reset_redirections();
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
