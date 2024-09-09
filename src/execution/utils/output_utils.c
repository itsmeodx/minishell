/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:42:55 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/09 18:51:42 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*get_output(char **cmd)
{
	pid_t	pid;
	int		fd[3];
	int		status;
	char	*output;

	output = NULL;
	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		fd[2] = open("/dev/null", O_WRONLY);
		dup2(fd[2], STDERR_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		return (close_pipe(fd), execve(cmd[0], cmd, NULL), close(fd[2]),
			exit(EXIT_FAILURE), NULL);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		output = get_next_line(fd[0]);
	if (output && output[ft_strlen(output) - 1] == '\n')
		output[ft_strlen(output) - 1] = '\0';
	return (close_pipe(fd), output);
}
