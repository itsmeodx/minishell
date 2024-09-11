/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:38:03 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/04 22:39:10 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	reset_redirections(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	execute_builtin(t_cmd *cmd)
{
	int			i;
	static char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	static bool	(*builtin_functions[])(t_cmd *) = {&builtin_echo, &builtin_cd,
		&builtin_pwd, &builtin_export, &builtin_unset, &builtin_env,
		&builtin_exit};

	i = -1;
	while (builtins[++i])
	{
		if (cmd && cmd->argv && !strcmp(cmd->argv[0], builtins[i]))
		{
			if (!set_redirections(cmd->redirections))
				return (g_data.exit_status = 1, EXIT_SUCCESS);
			builtin_functions[i](cmd);
			reset_redirections();
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
