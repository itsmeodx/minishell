/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:58:46 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/26 10:55:20 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

int	ft_get_fd(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	ft_error_msg(char *limit, int line_num)
{
	ft_dprintf(STDERR_FILENO, NAME
		"%s %d delimited by end-of-file (wanted `%s')\n",
		"warning: here-document at line", line_num, limit);
}

void	ft_write_n(char **line, int fd, int key_expand)
{
	if (!key_expand)
		*line = expand_dollar(*line);
	ft_dprintf(fd, "%s\n", *line);
	free(*line);
	*line = NULL;
}

char	*ft_write_heredoc(char *limit, int num, bool key_expand,
			int *status)
{
	char	*line;
	int		fd;
	pid_t	pid;

	line = ft_name_file(num);
	fd = ft_get_fd(line);
	pid = fork();
	if (pid == 0)
	{
		free(line);
		ft_fork_heredoc(limit, fd, key_expand);
	}
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	return (free(limit), close(fd), line);
}

int	ft_open_herdoc(t_link **link, bool key_expand, int num)
{
	t_link	*tmp;
	int		status;

	tmp = *link;
	status = 0;
	signal(SIGINT, SIG_IGN);
	while (tmp && status != 130)
	{
		if ((tmp)->identifier == HEREDOC
			&& ((tmp)->next && (tmp)->next->identifier == STR))
		{
			key_expand = is_inquotes((tmp)->next->command, 1);
			(tmp)->next->command
				= ft_tmp_rmquotes((tmp->next->command));
			(tmp)->next->command
				= ft_write_heredoc((tmp)->next->command,
					num++, key_expand, &status);
		}
		tmp = (tmp)->next;
	}
	signal(SIGINT, ft_signal);
	(status == 130) && (*link = NULL);
	(status == 130) && (g_data.exit_status = status);
	return (NONE);
}
