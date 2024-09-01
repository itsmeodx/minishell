/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:00:40 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/01 14:00:57 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

bool	set_redirections(t_redirection *redirections)
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
			return (dprintf(STDERR_FILENO,
					NAME "%s: ", redirections->file), perror(NULL), false);
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
	return (true);
}
