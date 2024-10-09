/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:00:40 by oouaadic          #+#    #+#             */
/*   Updated: 2024/09/28 11:46:39 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

void	reset_redirections(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static
bool	check_file(t_redirection *redirection)
{
	t_cmd	*cmd;
	char	*tmp;

	cmd = &(t_cmd){.argv = ft_strdup_2d((char *[]){redirection->file, NULL}),
		.argc = 1};
	ft_expansion(cmd);
	if (cmd->argc != 1 || !cmd->argv[0])
		return (ft_dprintf(STDERR_FILENO,
				NAME "%s: ambiguous redirect\n", redirection->file),
			free_2d(cmd->argv), false);
	tmp = redirection->file;
	redirection->file = cmd->argv[0];
	cmd->argv[0] = tmp;
	free_2d(cmd->argv);
	return (true);
}

bool	set_redirections(t_redirection *redirections)
{
	int	fd;

	while (redirections)
	{
		if (!check_file(redirections))
			return (false);
		if (redirections->identifier == IN
			|| redirections->identifier == HEREDOC)
			fd = open(redirections->file, O_RDONLY);
		else if (redirections->identifier == OUT)
			fd = open(redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redirections->identifier == APPEND)
			fd = open(redirections->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (ft_dprintf(STDERR_FILENO,
					NAME "%s: ", redirections->file), perror(NULL), false);
		if (redirections->identifier == IN
			|| redirections->identifier == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redirections = redirections->next;
	}
	return (true);
}
