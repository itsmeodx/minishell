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
#include "parsing.h"

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		if (!set_redirections(cmd->redirections))
			ft_exit(1);
		if ((cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
			&& access(cmd->argv[0], F_OK) != -1)
		{
			if (access(cmd->argv[0], X_OK) != -1)
			{
				execve(cmd->argv[0], cmd->argv, g_data.environ);
			}
			else
			{
				dprintf(STDERR_FILENO, NAME "%s: " PD "\n", cmd->argv[0]);
				ft_exit(126);
			}
		}
		else
		{
			ft_execvp(cmd->argv[0], cmd->argv);
			if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
				dprintf(STDERR_FILENO, NAME "%s: " NSFOD "\n", cmd->argv[0]);
			else
				dprintf(STDERR_FILENO, "%s: " CNF "\n", cmd->argv[0]);
			ft_exit(127);
		}
		ft_exit(1);
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

	if (!tree || !tree->cmd || !tree->cmd->argv || !tree->cmd->argv[0])
		return (EXIT_FAILURE);
	tree->cmd->redirections = tree->redirection;
	if (is_builtin(tree->cmd))
		status = execute_builtin(tree->cmd);
	else
		status = execute_cmd(tree->cmd);
	return (status);
}
