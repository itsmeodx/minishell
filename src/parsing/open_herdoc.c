/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhobba <akhobba@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:58:46 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/19 11:10:44 by akhobba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

bool	isempty(char	*line);

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
	dprintf(STDERR_FILENO, NAME
		"%s %d delimited by end-of-file (wanted `%s')\n",
		"warning: here-document at line", line_num, limit);
}

void	ft_write_n(char **line, int fd, int key_expand)
{
	if (!key_expand)
		line[1] = expand_env(line[1]);
	dprintf(fd, "%s\n", *line);
	free(*line);
	*line = NULL;
}

char	*ft_write_heredoc(char *limit, int num, bool key_expand)
{
	char	*line[2];
	int		line_num;
	int		fd;

	line[0] = ft_name_file(num);
	fd = ft_get_fd(line[0]);
	line_num = 0;
	while (true)
	{
		line[1] = readline("> ");
		if (line[1] && *line[1] && !isempty(line[1]))
			add_history(line[1]);
		if (++line_num && !line[1])
		{
			ft_error_msg(limit, line_num);
			break ;
		}
		if (*line[1] && ft_strncmp(line[1], limit, ft_strlen(line[1])) == 0)
		{
			free(line[1]);
			break ;
		}
		ft_write_n(&line[1], fd, key_expand);
	}
	return (free(limit), close(fd), line[0]);
}

int	ft_open_herdoc(t_link **link, bool key_expand)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (*link)
		{
			if ((*link)->identifier == HEREDOC
				&& ((*link)->next && (*link)->next->identifier == STR))
			{
				key_expand = is_inquotes((*link)->next->command, 1);
				(*link)->next->command
					= ft_tmp_rmquotes((*link)->next->command);
				(*link)->next->command
					= ft_write_heredoc((*link)->next->command,
						g_data.num_of_file++, key_expand);
			}
			*link = (*link)->next;
		}
		ft_exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	return (NONE);
}
