/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:12 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/04 22:50:51 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static
bool	isdir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (true);
	return (false);
}

static
void	execute_without_path(t_cmd *cmd)
{
	if (access(cmd->argv[0], F_OK) != -1)
	{
		if (isdir(cmd->argv[0]))
			dprintf(STDERR_FILENO, NAME "%s: " ISDIR "\n", cmd->argv[0]);
		else if (access(cmd->argv[0], X_OK) != -1)
			execve(cmd->argv[0], cmd->argv, g_data.environ);
		else
			dprintf(STDERR_FILENO, NAME "%s: " PD "\n", cmd->argv[0]);
		ft_exit(126);
	}
	else
	{
		dprintf(STDERR_FILENO, NAME "%s: " NSFOD "\n", cmd->argv[0]);
		ft_exit(127);
	}
}

static
void	execute_with_path(t_cmd *cmd)
{
	ft_execvpe(cmd->argv[0], cmd->argv, g_data.environ);
	dprintf(STDERR_FILENO, "%s: " CNF "\n", cmd->argv[0]);
	ft_exit(127);
}

int	execute_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		(!set_redirections(cmd->redirections)) && ft_exit(1);
		g_data.environ = filter_env(g_data.environ);
		if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
			execute_without_path(cmd);
		else
			execute_with_path(cmd);
	}
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_data.exit_status = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		g_data.exit_status = WSTOPSIG(status) + 128;
	else
		g_data.exit_status = 1;
	return (g_data.exit_status);
}

int	execute_str(t_tree *tree)
{
	if (!tree || !tree->cmd || !tree->cmd->argv || !tree->cmd->argv[0])
		return (EXIT_FAILURE);
	tree->cmd->redirections = tree->redirections;
	ft_expansion(tree->cmd->argv);
	if (!execute_builtin(tree->cmd))
		return (g_data.exit_status);
	else
		execute_cmd(tree->cmd);
	return (g_data.exit_status);
}
