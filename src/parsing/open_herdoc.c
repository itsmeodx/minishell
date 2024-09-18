/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:58:46 by akhobba           #+#    #+#             */
/*   Updated: 2024/09/18 13:16:14 by oouaadic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_name_file(int num_file)
{
	char	*num;
	char	*name;
	char	*file;
	int		fd;

	num = ft_itoa(num_file);
	name = malloc(ft_strlen(num) + 5);
	ft_strlcpy(name, HEREDOC, 4);
	ft_strlcpy(name + 3, num, ft_strlen(num) + 1);
	file = ft_strjoin("/tmp/", name);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free(name);
	free(num);
	free(file);
	return (fd);
}

void	ft_write_inherdoc(char *limit, int num)
{
	char	*line;
	char	*line_n;
	int		fd;

	fd = ft_name_file(num);
	while (true)
	{
		line = readline("> ");
		if (!line)
			continue ;
		line_n = ft_strjoin(line, "\n");
		ft_dprintf(fd, "%s", line_n);
		if (ft_strncmp(line, limit, 5) == 0)
		{
			free(line_n);
			free(line);
			break ;
		}
		num++;
		free(line);
		free(line_n);
	}
}

int	ft_open_herdoc(t_link *link)
{
	t_link	*tmp;
	int		num;

	num = 0;
	tmp = link;
	while (tmp)
	{
		if (tmp->identifier == HERDOC)
		{
			if (tmp->next && tmp->next->identifier == STR)
				ft_write_inherdoc(tmp->next->command, num);
			else
				return (ERROR_NUM_HERDOC);
			num++;
		}
		tmp = tmp->next;
	}
	return (true);
}
