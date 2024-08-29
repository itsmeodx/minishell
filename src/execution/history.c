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

static char	*get_next_line(int fd)
{
	char	*str;
	char	*buff;

	str = malloc(1000000);
	if (!str)
		return (NULL);
	buff = str;
	while (fd != -1 && read(fd, buff, 0) != -1 && read(fd, buff, 1)
		&& *buff++ != '\n');
	if (buff > str)
		return (*buff = 0, str);
	else
		return (free(str), NULL);
}

void	ft_add_history(char *line)
{
	int		fd;

	add_history(line);
	fd = open(".minishell_history", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return ;
	dprintf(fd, "%s\n", line);
	close(fd);
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
