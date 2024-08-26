/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:12 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/26 15:47:12 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		if ((cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
			&& access(cmd->argv[0], F_OK) != -1)
		{
			if (access(cmd->argv[0], X_OK) != -1)
			{
				execv(cmd->argv[0], cmd->argv);
			}
			else
			{
				dprintf(STDERR_FILENO, NAME"%s: "PD"\n",
					cmd->argv[0]);
				exit(126);
			}
		}
		else
		{
			execvp(cmd->argv[0], cmd->argv);
			if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
				dprintf(STDERR_FILENO, NAME"%s: "NSFOD"\n",
					cmd->argv[0]);
			else
				dprintf(STDERR_FILENO, "%s: "CNF"\n",
					cmd->argv[0]);
			exit(127);
		}
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	return (status);
}

int	execute_str(t_tree *tree)
{
	int	status;

	if (is_builtin(tree->cmd))
		status = execute_builtin(tree->cmd);
	else
		status = execute_cmd(tree->cmd);
	return (status);
}
