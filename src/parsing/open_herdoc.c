/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:58:46 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/19 09:47:52 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

bool	isempty(char	*line);

char	*ft_name_file(int num_file)
{
	char	*num;
	char	*file;

	num = ft_itoa(num_file);
	file = ft_strjoin(HEREDOC_PREFIX, num);
	if (access(file, F_OK) == 0)
		unlink(file);
	return (free(num), file);
}

int	ft_get_fd(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	ft_write_n(char **line, int fd)
{
	write(fd, *line, ft_strlen(*line));
	write(fd, "\n", 1);
	free(*line);
	*line = NULL;
}

char	*ft_write_heredoc(char *limit, int num, bool key_expand)
{
	char	*line;
	char	*file;
	int		line_num;
	int		fd;

	file = ft_name_file(num);
	fd = ft_get_fd(file);
	line_num = 1;
	while (true)
	{
		line = readline("> ");
		if (line && *line && !isempty(line))
			add_history(line);
		if (!line)
		{
			dprintf(STDERR_FILENO, NAME
				"warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
				line_num, limit);
			break ;
		}
		if (*line && ft_strncmp(line, limit, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		if (!key_expand)
			line = expand_env(line);
		ft_write_n(&line, fd);
		line_num++;
	}
	return (free(limit), close(fd),file);
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
			if ((*link)->identifier == HEREDOC &&
				((*link)->next && (*link)->next->identifier == STR))
				{
					key_expand = is_inquotes((*link)->next->command, 1);
					(*link)->next->command = ft_tmp_rmquotes((*link)->next->command);
					(*link)->next->command = ft_write_heredoc((*link)->next->command, g_data.num_of_file++,
					key_expand);
				}
			*link = (*link)->next;
		}
		ft_exit(EXIT_SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	return (NONE);
}
