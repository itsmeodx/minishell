/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:47:12 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 12:53:54 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

static
void	execute_without_path(t_cmd *cmd)
{
	if (access(cmd->argv[0], F_OK) != -1)
	{
		if (isdir(cmd->argv[0]))
			ft_dprintf(STDERR_FILENO, NAME "%s: " ISDIR "\n", cmd->argv[0]);
		else if (access(cmd->argv[0], X_OK) != -1)
			execve(cmd->argv[0], cmd->argv, g_data()->environ);
		else
			ft_dprintf(STDERR_FILENO, NAME "%s: " PD "\n", cmd->argv[0]);
		ft_exit(126);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, NAME);
		perror(cmd->argv[0]);
		ft_exit(127);
	}
}

static
void	execute_with_path(t_cmd *cmd)
{
	ft_execvpe(cmd->argv[0], cmd->argv, g_data()->environ);
	ft_dprintf(STDERR_FILENO, "%s: " CNF "\n", cmd->argv[0]);
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
		(reset_signals() && !set_redirections(cmd->redirections)) && ft_exit(1);
		g_data()->environ = filter_env(g_data()->environ);
		if (strchr(cmd->argv[0], '/') || !ft_getenv("PATH", g_data()->environ)
			|| !*ft_getenv("PATH", g_data()->environ))
			execute_without_path(cmd);
		else
			execute_with_path(cmd);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_data()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_data()->exit_status = WTERMSIG(status) + 128;
	else
		g_data()->exit_status = EXIT_FAILURE;
	return (g_data()->exit_status);
}

int	execute_str(t_tree *tree)
{
	if (!tree || !tree->cmd || !tree->cmd->argv || !*tree->cmd->argv)
	{
		if (tree)
			g_data()->exit_status = !set_redirections(tree->redirections);
		return (reset_redirections(), EXIT_SUCCESS);
	}
	tree->cmd->redirections = tree->redirections;
	ft_expansion(tree->cmd);
	if (!tree->cmd->argv || !*tree->cmd->argv)
		return (g_data()->exit_status = 0, EXIT_SUCCESS);
	if (execute_builtin(tree->cmd))
		execute_cmd(tree->cmd);
	if (is_in_env("_", g_data()->environ))
		update_env(g_data()->environ, "_",
			tree->cmd->argv[ft_strlen_2d(tree->cmd->argv) - 1]);
	else
		g_data()->environ = addtoenv(g_data()->environ, "_",
			tree->cmd->argv[ft_strlen_2d(tree->cmd->argv) - 1]);
	return (g_data()->exit_status);
}
