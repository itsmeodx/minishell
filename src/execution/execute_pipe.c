/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:58:19 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/01 14:47:57 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static
int	first_child(int *fd, t_tree *tree, pid_t *pids)
{
	pid_t	pid;
	int		status;

	pid = fork();
	*pids = pid;
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		status = ft_execution(tree);
		ft_exit(status);
	}
	return (EXIT_SUCCESS);
}

static
int	second_child(int *fd, t_tree *tree, pid_t *pids)
{
	pid_t	pid;
	int		status;

	pid = fork();
	*pids = pid;
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		status = ft_execution(tree);
		ft_exit(status);
	}
	return (EXIT_SUCCESS);
}

int	execute_pipe(t_tree *tree)
{
	int		fd[2];
	int		status;
	pid_t	pids[2];

	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	first_child(fd, tree->left, &pids[0]);
	second_child(fd, tree->right, &pids[1]);
	close_pipe(fd);
	waitpid(pids[0], &status, 0);
	waitpid(pids[1], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	else
		status = EXIT_FAILURE;
	return (g_data.exit_status = status, status);
}
