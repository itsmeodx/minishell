/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:58:19 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/26 15:58:19 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	first_child(int *fd, t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		status = ft_execution(tree);
		close_pipe(fd);
		exit(status);
	}
//	waitpid(pid, &status, 0);
//	if (WIFEXITED(status))
//	{
//		if (WEXITSTATUS(status) != 0)
//			return (EXIT_FAILURE);
//	}
//	else if (WIFSIGNALED(status))
//	{
//		if (WTERMSIG(status) + 128 != 0)
//			return (EXIT_FAILURE);
//	}
	return (EXIT_SUCCESS);
}

int	second_child(int *fd, t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		status = ft_execution(tree);
		exit(status);
	}
//	waitpid(pid, &status, 0);
//	if (WIFEXITED(status))
//	{
//		if (WEXITSTATUS(status) != 0)
//			return (EXIT_FAILURE);
//	}
//	else if (WIFSIGNALED(status))
//	{
//		if (WTERMSIG(status) + 128 != 0)
//			return (EXIT_FAILURE);
//	}
	return (EXIT_SUCCESS);
}

int	execute_pipe(t_tree *tree)
{
	int		fd[2];

	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	first_child(fd, tree->left);
	second_child(fd, tree->right);
	while (wait(NULL) != -1)
		;
	return (close_pipe(fd), EXIT_SUCCESS);
}
