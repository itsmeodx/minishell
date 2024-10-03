/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouaadic <oouaadic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:26:20 by adam              #+#    #+#             */
/*   Updated: 2024/10/03 10:23:11 by oouaadic         ###   ########.fr       */
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
char	*ft_tmp_rmquotes(char *(*str))
{
	char	c;
	int		i;
	int		j;
	int		key;

	j = 0;
	i = 0;
	key = 0;
	c = 0;
	if (!str || !(*str))
		return (NULL);
	while ((*str)[i])
	{
		if ((*str)[i] && ((*str)[i] == '"' || (*str)[i] == '\''))
		{
			c = (*str)[i++];
			while ((*str)[i])
			{
				if ((*str)[i] == c)
				{
					i++;
					c = 0;
				}
				(*str)[j++] = (*str)[i++];
			}
			if (!(*str)[i])
			{
				(*str)[j] = 0;
				break;
			}
		}
			(*str)[j++] = (*str)[i++];
	}
	return (NULL);
}
