/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by oouaadic          #+#    #+#             */
/*   Updated: 2024/08/29 18:03:37 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parsing.h"

char	*get_last_line(void)
{
	int		fd;
	char	*line;
	char	*last_line;

	fd = open(".minishell_history", O_RDONLY);
	if (fd == -1)
		return (NULL);
	last_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		free(last_line);
		last_line = line;
		line = get_next_line(fd);
	}
	if (last_line)
		last_line[strlen(last_line) - 1] = 0;
	close(fd);
	return (last_line);
}

bool	isempty(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;
	if (*line)
		return (false);
	return (true);
}

void	ft_add_history(char *line)
{
	int			fd;
	static char	*last_line = NULL;

	if (!last_line)
		last_line = get_last_line();
	if ((last_line && !strcmp(last_line, line)) || isempty(line))
		return ;
	free(last_line);
	last_line = ft_strdup(line);
	add_history(line);
	fd = open(".minishell_history", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return ;
	return (dprintf(fd, "%s\n", line), (void)close(fd));
}

void	restore_history(void)
{
	int		fd;
	char	*line;

	if (access(".minishell_history", F_OK) != -1)
	{
		if (access(".minishell_history", R_OK) == -1)
			unlink(".minishell_history");
		else if (access(".minishell_history", W_OK) == -1)
			unlink(".minishell_history");
	}
	fd = open(".minishell_history", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		line[strlen(line) - 1] = 0;
		add_history(line);
		free(line);
		line = get_next_line(fd);
	}
	return ((void)close(fd));
}
