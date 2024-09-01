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

static int	first_child(int *fd, t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
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

static int	second_child(int *fd, t_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
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
	int	fd[2];

	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	first_child(fd, tree->left);
	second_child(fd, tree->right);
	close_pipe(fd);
	while (wait(NULL) != -1)
		;
	return (EXIT_SUCCESS);
}
