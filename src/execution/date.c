/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   date.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:31:24 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/08 11:31:24 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*set_date(void)
{
	pid_t		pid;
	int			fd[2];
	static char	*date;
	int			status;

	if (pipe(fd) == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close_pipe(fd);
		execve("/bin/date", (char *[]){"date", "+%H:%M:%S %p", NULL},
			g_data.environ);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		date = get_next_line(fd[0]);
		date[strlen(date) - 1] = '\0';
	}
	return (close_pipe(fd), date);
}
