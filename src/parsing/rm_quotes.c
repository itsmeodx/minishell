/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adam <adam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:20 by adam              #+#    #+#             */
/*   Updated: 2024/10/06 18:18:20 by adam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "execution.h"

int	ft_fork_heredoc(char *limit, int fd, int key_expand)
{
	char	*line;
	int		line_num;

	line_num = 0;
	signal(SIGINT, ft_sigexit);
	while (true)
	{
		line = readline("> ");
		if (line && *line && !isempty(line))
			add_history(line);
		if (++line_num && !line)
		{
			ft_error_msg(limit, line_num);
			break ;
		}
		if (ft_strcmp(line, limit) == 0)
		{
			free(line);
			break ;
		}
		ft_write_n(&line, fd, key_expand);
	}
	return (close(fd), ft_exit(EXIT_SUCCESS), true);
}

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

size_t	ft_cal_whitoutquotes(char (*str))
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	if (ft_check_each_node(str) != true)
		return (0);
	while (str[i])
	{
		if (!(str[i] == '"' || str[i] == '\''))
			len++;
		i++;
	}
	return (len);
}

void	ft_tmp_rmquotes(char *(*str))
{
	char	c;
	int		i[2];

	c = 0;
	i[0] = 0;
	i[1] = 0;
	while ((*str)[i[0]])
	{
		if ((*str)[i[0]] && ((*str)[i[0]] == '"' || (*str)[i[0]] == '\''))
		{
			c = (*str)[i[0]++];
			while ((*str)[i[0]])
			{
				((*str)[i[0]] == c) && (i[0]++ && (c = 0));
				(*str)[i[1]++] = (*str)[i[0]++];
			}
			if (!(*str)[i[0]])
			{
				(*str)[i[1]] = 0;
				break ;
			}
		}
		(*str)[i[1]++] = (*str)[i[0]++];
	}
}
