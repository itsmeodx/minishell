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

void	set_redirections(t_redirection *redirections)
{
	int	fd;

	while (redirections)
	{
		if (redirections->identifier == IN)
			fd = open(redirections->file, O_RDONLY);
		else if (redirections->identifier == OUT)
			fd = open(redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redirections->identifier == APPEND)
			fd = open(redirections->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			dprintf(STDERR_FILENO, NAME "%s: " NSFOD "\n", redirections->file);
		else
		{
			if (redirections->identifier == IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redirections = redirections->next;
	}
}

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
		set_redirections(cmd->redirections);
		if ((cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
			&& access(cmd->argv[0], F_OK) != -1)
		{
			if (access(cmd->argv[0], X_OK) != -1)
			{
				execv(cmd->argv[0], cmd->argv);
			}
			else
			{
				dprintf(STDERR_FILENO, NAME "%s: " PD "\n", cmd->argv[0]);
				exit(126);
			}
		}
		else
		{
			execvp(cmd->argv[0], cmd->argv);
			if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
				dprintf(STDERR_FILENO, NAME "%s: " NSFOD "\n", cmd->argv[0]);
			else
				dprintf(STDERR_FILENO, "%s: " CNF "\n", cmd->argv[0]);
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

	tree->cmd->redirections = tree->redirection;
	if (is_builtin(tree->cmd))
		status = execute_builtin(tree->cmd);
	else
		status = execute_cmd(tree->cmd);
	return (status);
}
